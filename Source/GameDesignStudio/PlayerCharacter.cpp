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
/*
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

*/

