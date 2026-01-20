// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDynamic.h"

void APuzzleDynamic::BeginPlay()
{
	Super::BeginPlay();
	
	Location = GetActorLocation();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Location.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Puzzle Dynamic Begin Puzzle")));
	
}

// We could say we want this to activate another object after it's pushed or once it's
// reached a certain area, call a delegate
void APuzzleDynamic::PushObject(const FVector& Amount)
{
	//FVector NewLocation = GetActorLocation() + Amount;
	
	switch (State)
	{
	case EStates::State1:
		SetActorLocation(GetActorLocation() + Amount);
		
		break;
		
	case EStates::State2:
		SetActorLocation(GetActorLocation() - Amount);
		
	default:
		break;
	}
	
	/*
	if (State == EStates::State1)
	{
		FVector NewLocation = GetActorLocation() + Amount;
		SetActorLocation(NewLocation);
	}
	*/
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Puzzle Dynamic Push Object")));
	
}

