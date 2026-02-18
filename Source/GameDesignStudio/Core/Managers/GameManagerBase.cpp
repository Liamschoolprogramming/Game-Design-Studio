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



void UGameManagerBase::RegisterActor(const FName Id, const FPersistantActorValues& ActorValues)
{
	PersistantActorValues.Add(Id, ActorValues);
	
	if (const FPersistantActorValues* Data = PersistantActorValues.Find(Id))
	{
		UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Data->ActorLocation.GetLocation().ToString());
	}
}

void UGameManagerBase::Snapshot(const FName Id, const FPersistantActorValues& ActorValues)
{
	PersistantActorValues.Add(Id, ActorValues);

}

void UGameManagerBase::LoadActorState(const FName Id, const FPersistantActorValues& ActorValues)
{
	
}

