// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"

void APlayerControllerBase::ClickStarted()
{
	bSettingDestination = true;
}

void APlayerControllerBase::ClickEnded()
{
	bSettingDestination = false;
}


void APlayerControllerBase::Jump()
{
	if (IsValid(GetPawn()))
	{
		Cast<ACharacter>(GetPawn())->Jump();
	}
}

void APlayerControllerBase::StopJumping()
{
	if (IsValid(GetPawn()))
	{
		Cast<ACharacter>(GetPawn())->StopJumping();
	}
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
	EnhancedInput = CreateDefaultSubobject<UEnhancedInputComponent>("EnhancedInput");
		
		
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();


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

	if (JumpAction)
	{
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerControllerBase::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopJumping);
	}
	
}
