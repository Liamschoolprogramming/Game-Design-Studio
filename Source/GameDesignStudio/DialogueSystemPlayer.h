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






DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCustomFunctionParam, FString, FDialogueParameters)

UCLASS()
class GAMEDESIGNSTUDIO_API UDialogueSystemPlayer : public UObject, public IDialogueExecutionHandler
{
	GENERATED_BODY()

public:
	UDialogueSystemPlayer();
	// Pass delegate by value (Unreal-friendly)
	void PlayDialogue(UDialogueAsset* InDialogueAsset, 
					  APlayerController* InPlayerController);

	void ChooseOptionAtIndex(int Index);

	UDialogueSpeakerComponent* FindSpeakerComponent(UWorld* World, FName SpeakerName);
	
	ADialogueCineCamera* FindCineCamera(UWorld* World, FName InCameraName);
	
	UDialogueSpeakerComponent* CurrentSpeakerComponent = nullptr;

	FOnCustomFunctionParam OnCustomFunctionParam;
private:
	UPROPERTY()
	UDialogueAsset* PlayingDialogueAsset = nullptr;

	UPROPERTY()
	UDialogueRuntimeNode* CurrentNode = nullptr;

	UPROPERTY()
	UQuestDialogueUIController* DialogueWidget = nullptr;
	
	UPROPERTY()
	AActor* Owner;

	UTexture2D* DefaultCharacterIcon;
	
	APlayerControllerBase* PlayerController;
	

	UDialogueAsset* DialogueAsset;
	
	UFUNCTION()
	void ChooseFirstOption()
	{
		ChooseOptionAtIndex(0);
	}
	UFUNCTION()
	void ChooseFirstOptionAndEnableDialogue();

	
	
public:
	virtual void SetDialogueText(FText InText) override;
	virtual void ClearResponses() override;
	virtual void AddResponseButton(FText InResponseText, int InOptionIndex) override;
	virtual void SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, UTexture2D* Portrait) override;
	virtual void EndDialogue() override;
	virtual TArray<int> GetQuestProgress(FName QuestKey) override;
	virtual void StartQuest(FName QuestKey) override;
	virtual void CompleteQuest(FName QuestKey) override;
	virtual void CheckQuest(FName QuestKey) override;
	virtual void ChangeCamera(FName CameraName, float TransitionTime, bool bReenableDialogueAfterAnimation) override;
	virtual UObject* GetCurrentNode() override;
	virtual void CallCustomFunction(FString FunctionName) override;
	virtual UDialogueAsset* GetAsset() override;
	virtual void ChooseOption(int IndexToChoose) override;
	virtual UWorld* GetWorldFromPlayer() override;
	virtual void CheckDialogueState() override;
	virtual void PlayDialogue(AActor* InOwner, class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController) override;
	//virtual void CallCustomFunctionWithParams(FString FunctionName, const FDialogueParameters& Parameters) override;
};