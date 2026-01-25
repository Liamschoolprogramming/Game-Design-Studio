// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManagerBase.h"
#include "PuzzleRiverManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEDESIGNSTUDIO_API UPuzzleRiverManager : public UGameManagerBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FName NotBlueprintCreated;
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;
	virtual void Shutdown() override;
	
	UFUNCTION(BlueprintPure)
	int CalculateValues(int a, int b);
	
	UFUNCTION(BlueprintCallable)
	void TestingPuzzleNonBlueprint();
	
};
