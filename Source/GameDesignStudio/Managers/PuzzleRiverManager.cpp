// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleRiverManager.h"

#include "Kismet/GameplayStatics.h"

void UPuzzleRiverManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	NotBlueprintCreated = FName(TEXT("This wasn't created in blueprints"));
	
}

void UPuzzleRiverManager::Shutdown()
{
	// Replace with auto generating message
	UE_LOG(LogTemp, Log, TEXT("Puzzle River Manager Shutdown"));
}


int UPuzzleRiverManager::CalculateValues(int a,  int b)
{
	return a + b;
}

void UPuzzleRiverManager::TestingPuzzleNonBlueprint()
{
	
}

void UPuzzleRiverManager::SetPressurePlatePressed(bool BoolValue)
{
	PressurePlatePressed = BoolValue;
}