// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"

#include "GameManagerSubsystem.h"


void UPuzzleWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
	Super::Initialize(Collection);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Registered PuzzleWorldSubsystem")));
}

void UPuzzleWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPuzzleWorldSubsystem::RegisterPuzzleActor(APuzzle* Actor)
{
	
	UGameManagerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	
	
	if (!RuntimeActors.Contains(Actor->ActorId))
	{
		RuntimeActors.Add(Actor->ActorId, Actor);
		
		// Needs to get owning subsystem map of managers and use this as a key. Then call
		// register actor on the manager to register the actorValues struct by the ActorId key
		
		Subsystem->RegisterActorToManager(Actor->OwningManager, Actor->ActorId, Actor->ActorValues);
		
		UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Registered"), RuntimeActors.Num());
	
	}
	
	/*
	for (const auto& Actor :RuntimeActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor registered to WorldSubsystem"));
	}
	*/
}

void UPuzzleWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
	// Need to pass actor refs to managers after initialization
	
}
