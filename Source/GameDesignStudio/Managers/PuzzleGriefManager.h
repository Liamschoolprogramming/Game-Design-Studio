// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "GriefObject.h"
#include "PuzzleGriefManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UPuzzleGriefManager : public UGameManagerBase
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AGriefObject*> GriefObjects;
	
public:

	UFUNCTION()
	void RegisterGriefActor(AGriefObject* GriefObject);
	
	UFUNCTION(BlueprintCallable)
	void DisableAllGriefObjects();
};
