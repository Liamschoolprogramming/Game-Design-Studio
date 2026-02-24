// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueSpeakerComponent.h"

/**
 * 
 */

#include "DialoguePlayer.generated.h"

class UDialogueRuntimeNode;
class UDialogueAsset;
class UQuestDialogueUIController;

DECLARE_DELEGATE_TwoParams(FOnDialogueEnded, EDialogueNodeAction, FString);

UCLASS()
class GAMEDESIGNSTUDIO_API UDialoguePlayer : public UObject
{
	GENERATED_BODY()
public:
	void PlayDialogue(UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController, FOnDialogueEnded InOnDialogueEnded);
	
	void ChooseOptionAtIndex(int Index);
	
	UDialogueSpeakerComponent* FindSpeakerComponent(UWorld* World, FName SpeakerName);
	
private:
	UPROPERTY()
	UDialogueAsset* PlayingDialogueAsset = nullptr;
	UPROPERTY()
	UDialogueRuntimeNode* CurrentNode = nullptr;
	
	UPROPERTY()
	UQuestDialogueUIController* DialogueWidget = nullptr;
	
	FOnDialogueEnded OnDialogueEnded;
	
	
};
