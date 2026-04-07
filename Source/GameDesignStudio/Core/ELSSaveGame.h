// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/QuestData.h"
#include "GameFramework/SaveGame.h"
#include "Puzzles/Puzzle.h"
#include "Data/PuzzleWorldData.h"
#include "Puzzles/SaveStation.h"
#include "ELSSaveGame.generated.h"

USTRUCT()
struct FSaveData
{
	GENERATED_BODY()
public:
	
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

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FVector PlayerLocation;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	FRotator PlayerRotation;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	bool bIsAutoSave;


	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	TMap<FName, FQuest> Quests;
	
	UPROPERTY(SaveGame)
	TMap<FString, FPuzzleData> PuzzleData;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,SaveGame)
	TSoftObjectPtr<UWorld> World;
	
	UPROPERTY(SaveGame)
	TMap<FName, FPuzzleWorldData> AllWorldData;


	UPROPERTY(SaveGame)
	FSoftObjectPath ActiveSaveStationFile;

	
};
