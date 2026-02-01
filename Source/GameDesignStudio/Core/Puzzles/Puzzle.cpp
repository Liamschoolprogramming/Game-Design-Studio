// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"

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
	
	if (ActorId.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: ActorId must be set"), *GetName());
		
	}
	
	else
	{
		GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>()->RegisterPuzzleActor(this);
	}
	
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
void APuzzle::SetActorID(FName Id) const
{
	ActorId = Id;
}
*/

