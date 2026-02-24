#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueSpeakerComponent.h"

/**
 * 
 */

#include "DialogueSystemPlayer.generated.h"

// Forward declarations of any UObjects you reference in UPROPERTYs
class UDialogueAsset;
class UDialogueRuntimeNode;
class UQuestDialogueUIController;

// Unreal-style delegate instead of std::function
DECLARE_DELEGATE_TwoParams(FOnDialogueEnded, EDialogueNodeAction, FString);

UCLASS()
class GAMEDESIGNSTUDIO_API UDialogueSystemPlayer : public UObject
{
	GENERATED_BODY()

public:
	// Pass delegate by value (Unreal-friendly)
	void PlayDialogue(UDialogueAsset* InDialogueAsset, 
					  APlayerController* InPlayerController, 
					  FOnDialogueEnded InOnDialogueEnded);

	void ChooseOptionAtIndex(int Index);

	UDialogueSpeakerComponent* FindSpeakerComponent(UWorld* World, FName SpeakerName);
	
	UDialogueSpeakerComponent* CurrentSpeakerComponent = nullptr;

private:
	UPROPERTY()
	UDialogueAsset* PlayingDialogueAsset = nullptr;

	UPROPERTY()
	UDialogueRuntimeNode* CurrentNode = nullptr;

	UPROPERTY()
	UQuestDialogueUIController* DialogueWidget = nullptr;

	
	
	FOnDialogueEnded OnDialogueEnded;
};