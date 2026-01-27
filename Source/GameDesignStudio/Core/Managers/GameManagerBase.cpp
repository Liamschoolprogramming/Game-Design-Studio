// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerBase.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UGameManagerBase::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	// Registering with the service (subsystem)
	Owner = InstanceOwner;
	
	LogCreation();
}

void UGameManagerBase::PostInitialize()
{
	
}

void UGameManagerBase::Shutdown()
{
	
}

