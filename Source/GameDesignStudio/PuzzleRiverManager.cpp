// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleRiverManager.h"

void UPuzzleRiverManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Puzzle River Manager Initialized")));
	
	//UE_LOG(LogTemp, Log, TEXT("Puzzle River Manager Initialized"));
}

void UPuzzleRiverManager::Shutdown()
{
	UE_LOG(LogTemp, Log, TEXT("Puzzle River Manager Shutdown"));
}
