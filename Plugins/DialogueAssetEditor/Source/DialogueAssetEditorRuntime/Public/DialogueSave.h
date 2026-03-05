// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueSubsystem.h"
#include "GameFramework/SaveGame.h"
#include "DialogueSave.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	TMap<TSoftObjectPtr<UDialogueAsset>, FStateData> SavedDialogueTreeStates;
	
};
