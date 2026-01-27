// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableEntity.h"
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APossessableEntity::APossessableEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initialize camera arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 800;

	//Setup camera arm attach to the root component of the class
	CameraBoom->SetupAttachment(RootComponent);

	//use the pawn control rotation
	CameraBoom->bUsePawnControlRotation = true;

	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Set attach to the camera boom
	FollowCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void APossessableEntity::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void APossessableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APossessableEntity::OnTogglePossession()
{
	if (bPossessed)
	{
		PlayerController->Possess(PlayerCharacter);
		bPossessed = false;
	}
	else
	{
		PlayerController->Possess(this);
		bPossessed = true;
	}
}

void APossessableEntity::OnPossess()
{
	PlayerController->Possess(this);
	bPossessed = true;
}

void APossessableEntity::OnCancelPossess()
{
	PlayerController->Possess(PlayerCharacter);
	bPossessed = false;
}

void APossessableEntity::ClickStarted()
{
	bSettingDestination = true;
}

void APossessableEntity::ClickEnded()
{
	bSettingDestination = false;
}

void APossessableEntity::MoveForward(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		//find which direction is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void APossessableEntity::MoveRight(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		//find which direction is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void APossessableEntity::Look(const FInputActionValue& Value)
{
	if (bSettingDestination) return;
	FVector2D LookVector = Value.Get<FVector2D>();
	
	DoLook(LookVector.X, LookVector.Y);
}

void APossessableEntity::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APossessableEntity::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void APossessableEntity::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}
	
void APossessableEntity::Zoom(const FInputActionValue& Value)
{
	float AxisValue = -Value.Get<float>();
	float NewZoom = AxisValue * CameraZoomSpeed;
	
	//calculate new zoom within range
	float length = CameraBoom->TargetArmLength;

	if (NewZoom + length > CameraZoomMax)
	{
		NewZoom = CameraZoomMax;
	}
	else if (NewZoom + length < CameraZoomMin)
	{
		NewZoom = CameraZoomMin;
	}
	else
	{
		NewZoom = NewZoom + length;
	}

	CameraBoom->TargetArmLength = NewZoom;

	//Update the cutout distance in the MPC
	if (!CameraMPC) return;
	UMaterialParameterCollectionInstance* MPCInstance =
		GetWorld()->GetParameterCollectionInstance(CameraMPC);
	if (!MPCInstance) return;
	MPCInstance->SetScalarParameterValue(
		FName("CameraArmLength"),(length-CameraCutoutCompensation)
	);

}

// Called to bind functionality to input
void APossessableEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		//zoom
		EnhancedInput->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APossessableEntity::Zoom);
		
		// Moving
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APossessableEntity::Move);
		
		// Mouse look
		EnhancedInput->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APossessableEntity::Look);

		// Looking
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APossessableEntity::Look);
		
		//Click
		EnhancedInput->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APossessableEntity::ClickStarted);
		EnhancedInput->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APossessableEntity::ClickEnded);
		
		// Cancel Possession
		EnhancedInput->BindAction(CancelPossessAction, ETriggerEvent::Triggered, this, &APossessableEntity::OnCancelPossess);
	}
}
