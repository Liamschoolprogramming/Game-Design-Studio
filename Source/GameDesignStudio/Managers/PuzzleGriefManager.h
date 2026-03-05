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
	TArray<AActor*> GriefObjects;
	
public:

	UFUNCTION(BlueprintCallable)
	void RegisterGriefActor(AActor* GriefObject);
	
	UFUNCTION(BlueprintCallable)
	void DisableAllGriefObjects();
	
	UFUNCTION(BlueprintCallable)
	void EnableAllGriefObjects();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool solved;
};
