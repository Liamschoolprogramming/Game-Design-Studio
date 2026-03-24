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

void UPuzzleWorldSubsystem::RegisterPuzzleActor(APuzzle* Actor)
{
	
	UGameManagerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	
	if (!RuntimeActors.Contains(Actor->PuzzleActorGuid))
	{
		// Registering actor references with the PuzzleWorldSubsystem
		RuntimeActors.Add(Actor->PuzzleActorGuid, Actor);
		
		// Registering actor with the manager set in the editor and storing initial data
		Subsystem->RegisterActorToManager(Actor->OwningManager, Actor->PuzzleActorGuid, Actor->ActorValues);
		UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Registered %d"), RuntimeActors.Num());
	
	}
}

TArray<APuzzle*> UPuzzleWorldSubsystem::GetActorsOfManagerType(TSubclassOf<UGameManagerBase> Manager)
{
	TArray<APuzzle*> Actors;
	
	for (const TPair<FGuid, TWeakObjectPtr<APuzzle>>& Pair : RuntimeActors)
	{
		APuzzle* Actor = Pair.Value.Get();
		
		if (Actor->OwningManager == Manager)
		{
			Actors.Add(Actor);
		}
	}
	
	return Actors;
}

void UPuzzleWorldSubsystem::SaveAll(UELSSaveGame* SaveGame)
{
	for (auto& [Guid, Puzzle] : RuntimeActors)
	{
		// Generate GUID on first save if not already set
		if (!Puzzle->PuzzleActorGuid.IsValid())
		{
			Puzzle->PuzzleActorGuid = FGuid::NewGuid();
		}

		FPuzzleData Data;
		Puzzle->SaveData(Data);
		SaveGame->PuzzleData.Add(Puzzle->PuzzleActorGuid, Data);
	}
}

void UPuzzleWorldSubsystem::LoadAll(UELSSaveGame* SaveGame)
{
	UE_LOG(LogTemp, Warning, TEXT("Loading Puzzle Actors from array"));
	for (auto& [Guid, Puzzle] : RuntimeActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Loading"));
		if (FPuzzleData* Data = SaveGame->PuzzleData.Find(Puzzle->PuzzleActorGuid))
		{
			UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Found"));
			// Found in save — restore state
			Puzzle->LoadData(*Data);
		}
		else
		{
			// Not saved before — first time seeing this puzzle
			UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Not Found"));
			Puzzle->InitializePuzzleDefaults();
		}
	}
	
}


void UPuzzleWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
}
