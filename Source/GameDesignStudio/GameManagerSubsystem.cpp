// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerSubsystem.h"
#include "GameManagerBase.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// What is actually spawning the managers
	RegisterManagers();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Registered GameManagerSubsystem")));
	
	// Calling initialize on each manager in the array and setting its
	// instance owner to this subsystem
	
	// Pair.Value is accessing the manager at the current index in the range
	// then we use the arrow operator to call initialize of that instance and
	// pass this subsytem as an arugement
	for (auto& Pair : Managers)
	{
		Pair.Value->Initialize(this);
	}
	
	
	for (auto& Pair : Managers)
	{
		Pair.Value->Initialize(this);
	}
	
}

void UGameManagerSubsystem::Deinitialize()
{
	for (auto& Pair : Managers)
	{
		Pair.Value->Shutdown();
	}
	
	Managers.Empty();
	
	Super::Deinitialize();
}


void UGameManagerSubsystem::RegisterManagers()
{
	RegisterManager<UGameManagerBase>();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Added Manager")));
}

template <typename T>
void UGameManagerSubsystem::RegisterManager()
{
	T* Manager = NewObject<T>(this);
	Managers.Add(T::StaticClass(), Manager);
}

/*
UGameManagerBase* UGameManagerSubsystem::GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass) const
{
	return nullptr;
}
*/
