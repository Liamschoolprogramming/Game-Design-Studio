// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTypes.generated.h"

/**
 * 
 */

// Add more structs for more features

USTRUCT(BlueprintType)
struct FPuzzleId
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Area;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;
};

enum class EPuzzleStatus : uint8
{
	Inactive,
	Active,
	Solved,
	Failed,
};
