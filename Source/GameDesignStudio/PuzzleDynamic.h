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
	
public:
	virtual void PushObject(const FVector& Amount) override;

protected:
	virtual void BeginPlay() override;
	
};
