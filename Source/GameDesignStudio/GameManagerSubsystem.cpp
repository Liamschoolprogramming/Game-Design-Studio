// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerSubsystem.h"
#include "GameManagerBase.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	RegisterManagers();
	
	
}

void UGameManagerSubsystem::Deinitialize()
{
	
	Super::Deinitialize();
}

void UGameManagerSubsystem::RegisterManagers()
{
	
}

UGameManagerBase* UGameManagerSubsystem::GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass) const
{
	return nullptr;
}
