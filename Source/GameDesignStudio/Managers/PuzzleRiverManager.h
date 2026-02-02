// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
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
	
	UFUNCTION(Blueprintable)
	void SetPressurePlatePressed(bool BoolValue);
	
	UFUNCTION(BlueprintPure)
	int CalculateValues(int a, int b);
	
	UFUNCTION(BlueprintCallable)
	void TestingPuzzleNonBlueprint();
	
	UPROPERTY(BlueprintReadWrite)
	bool PressurePlatePressed;
	
	UPROPERTY(BlueprintReadWrite)
	bool ColumnKnockedDown;
	
};
