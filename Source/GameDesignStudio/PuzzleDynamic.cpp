// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDynamic.h"

void APuzzleDynamic::BeginPlay()
{
	Super::BeginPlay();
	
	Location = GetActorLocation();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Location.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Puzzle Dynamic Begin Puzzle")));

	
	
	
	
	
}

