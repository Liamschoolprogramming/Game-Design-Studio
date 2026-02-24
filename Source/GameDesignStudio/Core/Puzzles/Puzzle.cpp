// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/PuzzleRiverManager.h"
#include "Core/Subsystems/PuzzleWorldSubsystem.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	ActorValues.ActorLocation = GetActorTransform();
	
	//************************************************************************************//
	// SetState should maybe be called after registration. Might need to change where the
	// error handling happens from SnapshotActorValues if it does
	//************************************************************************************//
	SetState(PuzzleStatus);
	
	GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>()->RegisterPuzzleActor(this);
	
	if (LinkedReceiver != nullptr)
	{
		LinkedReceiver->Signals.Add(this->GetActorGuid(), false);
	}
}

// Getting the name of the current enum state to store
// on the manager to later be compared
void APuzzle::SetState(EPuzzleState State)
{
	PuzzleStatus = State;
	
	// GetSubsystem<UGameManagerSubsystem>()
	
	// Passes the instance object for the arguement
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->SnapshotActorValues(this);
}

void APuzzle::ApplyPuzzleState_Implementation()
{
	
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzle::ApplyState(const FPersistantActorValues& State)
{
	SetActorTransform(State.ActorLocation);
	
}



