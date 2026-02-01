// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"


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
	
	RuntimeActors.Add(Actor->ActorId);
	
	UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Registered"), RuntimeActors.Num());
	
	
	
	/*
	for (const auto& Actor :RuntimeActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor registered to WorldSubsystem"));
	}
	*/
}