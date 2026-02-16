// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"
#include "GameManagerSubsystem.h"


void UPuzzleWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
	Super::Initialize(Collection);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Registered PuzzleWorldSubsystem")));
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
		// Registering actor references with the PuzzleWorldSubsystem
		RuntimeActors.Add(Actor->ActorId, Actor);
		
		// Registering actor with the manager set in the editor and storing initial data
		Subsystem->RegisterActorToManager(Actor->OwningManager, Actor->ActorId, Actor->ActorValues);
		UE_LOG(LogTemp, Warning, TEXT("Puzzle Actor Registered %d"), RuntimeActors.Num());
	
	}
}

TArray<APuzzle*> UPuzzleWorldSubsystem::GetActorsOfManagerType(TSubclassOf<UGameManagerBase> Manager)
{
	TArray<APuzzle*> Actors;
	
	for (const TPair<FName, TWeakObjectPtr<APuzzle>>& Pair : RuntimeActors)
	{
		APuzzle* Actor = Pair.Value.Get();
		
		if (Actor->OwningManager == Manager)
		{
			Actors.Add(Actor);
		}
	}
	
	return Actors;
}

void UPuzzleWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
}
