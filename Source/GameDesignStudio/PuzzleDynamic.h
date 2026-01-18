// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleDynamic.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleDynamic : public APuzzle
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
