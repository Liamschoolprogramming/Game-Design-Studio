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
	SetState(PuzzleStatus);
	
	if (ActorId.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: ActorId must be set"), *GetName());
		
	}
	
	else
	{
		GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>()->RegisterPuzzleActor(this);
	}
	
}

//void APuzzle::InitializeState()
//{
	//const UEnum* Enum = StaticEnum<EPuzzleStatus>();
	
	//FName StateName = Enum->GetNameByValue(static_cast<int64>(PuzzleStatus));
	//StateName = FName(*Enum->GetNameStringByValue(static_cast<int64>(PuzzleStatus)));
	
	//ActorValues.CurrentState = StateName;
	
	//IsOpen = ActorStates.State.Contains(EPuzzleStatus::Start)
	
	//ActorValues.States.Add(StateName);
//}


// Getting the name of the current enum state to store
// on the manager to later be compared
void APuzzle::SetState(EPuzzleState State)
{
	//***************************************************//
	// For debug display naming of states
	//const UEnum* Enum = StaticEnum<EPuzzleState>();
	
	//FName StateName = Enum->GetNameByValue(static_cast<int64>(State));
	//StateName = FName(*Enum->GetNameStringByValue(static_cast<int64>(PuzzleStatus)));
	//****************************************************//
	
	PuzzleStatus = State;
	
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->SnapshotActorValues(this);
	
	//ActorValues.CurrentState = StateName;
}


// Call Super first when implementing custom functionality 
// to make sure the state is set properly

/*
void DoActionBasedOnState(FName State)
{
	
}
*/

/*
UGameManagerBase* APuzzle::GetOwningManagerClass()
{
	
	UGameManagerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	UGameManagerBase* Manager = Subsystem->GetManagerByClass(OwningManager);
	
	return Manager;
}
*/

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

