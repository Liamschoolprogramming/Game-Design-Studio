// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

DECLARE_DELEGATE_OneParam(FHardwareDelegate, FHardwareInputDeviceChanged);


void APlayerControllerBase::Jump(const FInputActionValue& Value)
{
	//Get the pawn we are possessing, if it is a character we can just call Jump, if not, add custom jump logic
	ACharacter* OurCharacter = Cast<ACharacter>(GetPawn());
	if (OurCharacter)
	{
		OurCharacter->Jump();
		
	}
	
}

void APlayerControllerBase::StopJumping(const FInputActionValue& Value)
{
	//Get the pawn we are possessing, if it is a character we can just call Jump, if not, add custom jump logic
	ACharacter* OurCharacter = Cast<ACharacter>(GetPawn());
	if (OurCharacter)
	{
		OurCharacter->StopJumping();
	}
}

void APlayerControllerBase::StartClick(const FInputActionValue& Value)
{
	//Do the move to here instead of blueprints
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility,true, Hit);
	
	if (Hit.bBlockingHit && CameraReference->bLockCameraToCharacter == true)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
	}
}

void APlayerControllerBase::StopClick(const FInputActionValue& Value)
{
}

void APlayerControllerBase::LookGate(const FInputActionValue& Value)
{
	
	
}

void APlayerControllerBase::LookGateStart()
{
	if (CameraReference)
	{
		CameraReference->AllowCameraRotation(true);
	}
}

void APlayerControllerBase::LookGateStop()
{
	if (CameraReference)
	{
		CameraReference->AllowCameraRotation(false);
	}
}


void APlayerControllerBase::ToggleLockCameraToPawn(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.4, FColor::Red, "ToggleLockCameraToPawn");
	if (CameraReference)
	{
		CameraReference->bLockCameraToCharacter = !(CameraReference->bLockCameraToCharacter);
		CameraReference->AllowCameraRotation(false);
	}
}

void APlayerControllerBase::Select(const FInputActionValue& Value)
{
	
	
}

void APlayerControllerBase::Zoom(const FInputActionValue& Value)
{
	if (CameraReference)
	{
		CameraReference->ZoomCamera(Value.Get<float>());
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, "ZoomCamera");
	}
}

void APlayerControllerBase::Look(const FInputActionValue& Value)
{
	if (CameraReference)
	{
		if (bUsingGamepad)
		{
			CameraReference->AllowCameraRotation(true);
		}
		
		CameraReference->RotateCamera(Value.Get<FVector2D>());
	}
}

void APlayerControllerBase::Move(const FInputActionValue& Value)
{
	//move the camera if we have a reference to it
	if (CameraReference)
	{
		if (CameraReference->bLockCameraToCharacter == false)
		{
			CameraReference->MoveCamera(Value.Get<FVector2D>());
		}
		
	}
}

void APlayerControllerBase::DoMove(float Right, float Forward)
{
}

void APlayerControllerBase::DoLook(float Yaw, float Pitch)
{
}

APlayerControllerBase::APlayerControllerBase()
{
	
		
		FHardwareDelegate HardwareDelegate;
	
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//spawn camera
	if (CameraReferenceClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
		FVector _SpawnLocation = GetPawn()->GetActorLocation();
		
		FRotator _SpawnRotation = GetPawn()->GetActorRotation();
		APlayerCameraManager* pcm = PlayerCameraManager.Get();
		
		
		CameraReference = GetWorld()->SpawnActor<ACustomCamera>(ACustomCamera::StaticClass(), _SpawnLocation, _SpawnRotation, SpawnParams);
	
		SetViewTarget(CameraReference);
		if (pcm && CameraReference)
		{
			CameraReference->pitchMax = PlayerCameraManager.Get()->ViewPitchMax;
			CameraReference->pitchMin = PlayerCameraManager.Get()->ViewPitchMin;
		}
	}
	
	//set up input
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	
	
	//setup cursor 
	bShowMouseCursor = true;
	bEnableClickEvents = true;

	
	
	
}

void APlayerControllerBase::CheckControlDevice(FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId)
{
	UInputDeviceSubsystem* InputDeviceSubsystem  = UInputDeviceSubsystem::Get();
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (InputDeviceSubsystem  && LocalPlayer)
	{
		
		FHardwareDeviceIdentifier  DeviceType = InputDeviceSubsystem->GetInputDeviceHardwareIdentifier (InputDeviceId);
	 
		if (DeviceType.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Gamepad");
			bUsingGamepad = true;
		}
		else if (DeviceType.PrimaryDeviceType == EHardwareDevicePrimaryType::KeyboardAndMouse)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Player is using Keyboard and Mouse");
			bUsingGamepad = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Player is using another device");
			bUsingGamepad = false;
		}
		
	}
}

//bind all input actions
void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ZoomAction)
		{
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Zoom);
		}
		
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
		}
		
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Look);
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Look");
		}
		if (JumpAction)
		{
			
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerControllerBase::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopJumping);
		}
		if (SetDestinationClickAction)
		{
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APlayerControllerBase::StartClick);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopClick);
		}
		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Look);
		}
		if (LookGateAction)
		{
			EnhancedInputComponent->BindAction(LookGateAction, ETriggerEvent::Started, this, &APlayerControllerBase::LookGateStart);
			EnhancedInputComponent->BindAction(LookGateAction, ETriggerEvent::Completed, this, &APlayerControllerBase::LookGateStop);
			
		}
		if (ToggleLockCameraToPawnAction)
		{
			EnhancedInputComponent->BindAction(ToggleLockCameraToPawnAction,ETriggerEvent::Completed, this, &APlayerControllerBase::ToggleLockCameraToPawn);
		}
		if (SelectAction)
		{
			EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Select);
		}
		
	}
}
