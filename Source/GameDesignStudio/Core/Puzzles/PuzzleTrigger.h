// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "GameFramework/Actor.h"
#include "PuzzleTrigger.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleTrigger : public APuzzle
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable) 
	void EmitGreenSignal();
	
	UFUNCTION(BlueprintCallable) 
	void EmitRedSignal();

public:
	APuzzleTrigger();
};
