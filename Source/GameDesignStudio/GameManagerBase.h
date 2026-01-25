// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PuzzleTypes.h"
#include "GameManagerBase.generated.h"

/**
 * 
 */

class UGameManagerSubsystem;

UCLASS(Abstract, BlueprintType, Blueprintable)
class GAMEDESIGNSTUDIO_API UGameManagerBase : public UObject
{
	GENERATED_BODY()

public:
	
	// Sets the owning subsystem
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner);
	
	virtual void Shutdown();
	
	virtual void PostInitialize();
	
	UFUNCTION(BlueprintPure, Category = "Puzzle")
	bool IsPuzzleSolved(const FPuzzleId& Id) const;
	
	void SetPuzzleStep(const FPuzzleId& Id, FName StepId);
	
protected:
	
	UPROPERTY()
	TObjectPtr<UGameManagerSubsystem> Owner;
	
	// Easier to just inline. If we have lots of classes to lookup, might want to
	// put in cpp file
	void LogCreation() const
	{
		UE_LOG(LogTemp, Warning, TEXT("Manager created: %s"), *GetClass()->GetName());
	}
	
};
