// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"




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
}

void APlayerControllerBase::StopClick(const FInputActionValue& Value)
{
}

void APlayerControllerBase::LookGate(const FInputActionValue& Value)
{
}

void APlayerControllerBase::ToggleLockCameraToPawn(const FInputActionValue& Value)
{
}

void APlayerControllerBase::Select(const FInputActionValue& Value)
{
}

void APlayerControllerBase::Zoom(const FInputActionValue& Value)
{
	
}

void APlayerControllerBase::Look(const FInputActionValue& Value)
{
}

void APlayerControllerBase::Move(const FInputActionValue& Value)
{
	
}

void APlayerControllerBase::DoMove(float Right, float Forward)
{
}

void APlayerControllerBase::DoLook(float Yaw, float Pitch)
{
}

APlayerControllerBase::APlayerControllerBase()
{
	
		
		
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (CameraReferenceClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
		FVector _SpawnLocation = GetPawn()->GetActorLocation();
		
		FRotator _SpawnRotation = GetPawn()->GetActorRotation();
		
	
		CameraReference = GetWorld()->SpawnActor<ACustomCamera>(ACustomCamera::StaticClass(), _SpawnLocation, _SpawnRotation, SpawnParams);
	
		SetViewTarget(CameraReference);
	}
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	bShowMouseCursor = true;
	bEnableClickEvents = true;

	
	
	
}

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
			EnhancedInputComponent->BindAction(LookGateAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::LookGate);
			
		}
		if (ToggleLockCameraToPawnAction)
		{
			EnhancedInputComponent->BindAction(ToggleLockCameraToPawnAction,ETriggerEvent::Triggered, this, &APlayerControllerBase::ToggleLockCameraToPawn);
		}
		if (SelectAction)
		{
			EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Select);
		}
		
	}
}
