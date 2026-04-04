// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MetaSave.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UMetaSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meta", SaveGame)
	TMap<FString, FDateTime> SaveSlotList;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meta", SaveGame)
	FString CurrentSave;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meta", SaveGame)
	int32 MaxAutoSaves = 4;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meta", SaveGame)
	float AutoSaveFrequency = 600.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Meta", SaveGame)
	TArray<FString> AutoSaveKeys;
};
