// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ELSSaveGame.generated.h"

USTRUCT()
struct FSaveData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float MindStat;
	UPROPERTY()
	float StaminaStat;
	UPROPERTY()
	int QuestsComplete;
	
};

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UELSSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	float MindStat;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	float StaminaStat;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	int QuestsComplete;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	float TimePlayed;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FDateTime StartDate;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FDateTime LastSaveDate;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FString ScreenshotPath;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FString SlotName;
	
};
