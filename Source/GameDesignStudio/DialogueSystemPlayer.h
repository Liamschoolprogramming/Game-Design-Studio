#pragma once

#include "CoreMinimal.h"
#include "DialogueCineCamera.h"
#include "UObject/Object.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueSpeakerComponent.h"

/**
 * 
 */

#include "DialogueSystemPlayer.generated.h"

class APlayerControllerBase;
// Forward declarations of any UObjects you reference in UPROPERTYs
class UDialogueAsset;
class UDialogueRuntimeNode;
class UQuestDialogueUIController;

// Unreal-style delegate instead of std::function
DECLARE_DELEGATE_TwoParams(FOnDialogueEnded, EDialogueNodeAction, FString);

UCLASS()
class GAMEDESIGNSTUDIO_API UDialogueSystemPlayer : public UObject, public IDialogueExecutionHandler
{
	GENERATED_BODY()

public:
	UDialogueSystemPlayer();
	// Pass delegate by value (Unreal-friendly)
	void PlayDialogue(UDialogueAsset* InDialogueAsset, 
					  APlayerController* InPlayerController, 
					  FOnDialogueEnded InOnDialogueEnded);

	void ChooseOptionAtIndex(int Index);

	UDialogueSpeakerComponent* FindSpeakerComponent(UWorld* World, FName SpeakerName);
	
	ADialogueCineCamera* FindCineCamera(UWorld* World, FName InCameraName);
	
	UDialogueSpeakerComponent* CurrentSpeakerComponent = nullptr;

private:
	UPROPERTY()
	UDialogueAsset* PlayingDialogueAsset = nullptr;

	UPROPERTY()
	UDialogueRuntimeNode* CurrentNode = nullptr;

	UPROPERTY()
	UQuestDialogueUIController* DialogueWidget = nullptr;

	UTexture2D* DefaultCharacterIcon;
	
	APlayerControllerBase* PlayerController;
	
	FOnDialogueEnded OnDialogueEnded;
	
public:
	virtual void SetDialogueText(FText InText) override;
	virtual void ClearResponses() override;
	virtual void AddResponseButton(FText InResponseText, int InOptionIndex) override;
	virtual void SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, UTexture2D* Portrait) override;
	virtual void EndDialogue(EDialogueNodeAction Action, FString ActionData) override;
	virtual TArray<int> GetQuestProgress(FName QuestKey) override;
	virtual void StartQuest(FName QuestKey) override;
	virtual void CompleteQuest(FName QuestKey) override;
	virtual void CheckQuest(FName QuestKey) override;
	virtual void ChangeCamera(FName CameraName, float TransitionTime) override;
};