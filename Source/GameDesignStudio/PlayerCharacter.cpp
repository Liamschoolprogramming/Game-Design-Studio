// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	
	//Initialize camera arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	//Setup camera arm 
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	
	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Setup camera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
}
// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		//zoom
		EnhancedInput->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Zoom);
		
		//jump
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		//Mouse look
		EnhancedInput->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Looking
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		//Click
		EnhancedInput->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APlayerCharacter::ClickStarted);
		EnhancedInput->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APlayerCharacter::ClickEnded);
		
	}
}

void APlayerCharacter::MoveForward(float AxisValue)
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

void APlayerCharacter::ClickStarted()
{
	bSettingDestination = true;
}

void APlayerCharacter::ClickEnded()
{
	bSettingDestination = false;
}

void APlayerCharacter::MoveRight(float AxisValue)
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
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
	//Update the cutout distance in the MPC
	if (!CameraMPC) return;
	UMaterialParameterCollectionInstance* MPCInstance =
		GetWorld()->GetParameterCollectionInstance(CameraMPC);
	if (!MPCInstance) return;
	MPCInstance->SetScalarParameterValue(
		FName("CameraArmLength"),((CameraBoom->TargetArmLength)-CameraCutoutCompensation)
	);
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APlayerCharacter::Zoom(const FInputActionValue& Value)
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
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	//we dont want to move the camera while trying to click to move
	if (bSettingDestination) return;
	FVector2D LookVector = Value.Get<FVector2D>();
	
	DoLook(LookVector.X, LookVector.Y);
	
	
	
}

void APlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void APlayerCharacter::DoMove(float Right, float Forward)
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
//Handle jump in BP exposed functions
void APlayerCharacter::DoJumpStart()
{
	ACharacter::Jump();
}

void APlayerCharacter::DoJumpEnd()
{
	ACharacter::StopJumping();
}

void APlayerCharacter::DoKnockback(float _power, AActor* origin)
{
	
	FVector locations;
	locations = this->GetActorLocation() - origin->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.X) // The message itself as an FString

	);
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.Y) // The message itself as an FString

	);
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.Z) // The message itself as an FString

	);
	locations *= FVector(1,1,0);
	
	locations = locations.GetSafeNormal(1.0);
	
	locations.Normalize(1.0);
	
	LaunchCharacter(locations * _power, false, false);
}


