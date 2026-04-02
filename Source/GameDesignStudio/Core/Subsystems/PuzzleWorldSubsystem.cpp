// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"
#include "GameManagerSubsystem.h"


void UPuzzleWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	DEBUG_TO_SCREEN(FColor::Emerald, "Registered PuzzleWorldSubsystem");
}

void UPuzzleWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
}



void UPuzzleWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
}

void UPuzzleWorldSubsystem::RegisterPuzzleOwner(APuzzleOwner* InPuzzleOwner)
{
	PuzzleOwners.Add(InPuzzleOwner);
}

TArray<FPuzzleOwnerData> UPuzzleWorldSubsystem::CaptureAllStates()
{
	TArray<FPuzzleOwnerData> States;
	for (auto* PuzzleOwner : PuzzleOwners)
	{
		States.Add(PuzzleOwner->CaptureState());
	}
	return States;
}

void UPuzzleWorldSubsystem::RestoreAllStates(const TArray<FPuzzleOwnerData>& AllStates)
{
	for (auto Data : AllStates)
	{
		for (auto* PuzzleOwner : PuzzleOwners)
		{
			if (PuzzleOwner->PuzzleName == Data.PuzzleName)
			{
				PuzzleOwner->RestoreState(Data);
				break;
			}
		}
	}
}
