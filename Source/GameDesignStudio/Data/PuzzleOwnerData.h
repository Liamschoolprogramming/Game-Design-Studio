// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleOwnerData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPuzzleOwnerData
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(SaveGame)
	FName PuzzleName;
	
	UPROPERTY(SaveGame)
	bool bIsSolved;
	
	
	
};
