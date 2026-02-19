// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API USettingsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", SaveGame)
	float MusicVolume = 0.75f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", SaveGame)
	float SFXVolume = 0.75f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", SaveGame)
	float MasterVolume =1.0f;
};
