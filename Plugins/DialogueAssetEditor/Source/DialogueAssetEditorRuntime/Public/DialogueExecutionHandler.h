// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueNodeInfoBase.h"
#include "UObject/Interface.h"

#include "DialogueExecutionHandler.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDialogueExecutionHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUEASSETEDITORRUNTIME_API IDialogueExecutionHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetDialogueText(FText InText) = 0;
	virtual void ClearResponses() = 0;
	virtual void AddResponseButton(FText InResponseText, int InOptionIndex) = 0;
	virtual void SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, UTexture2D* Portrait) = 0;
	virtual void EndDialogue(EDialogueNodeAction Action, FString ActionData) = 0;
	virtual TArray<int> GetQuestProgress(FName QuestKey) = 0;
	virtual void StartQuest(FName QuestKey) = 0;
	virtual void CompleteQuest(FName QuestKey) = 0;
	virtual void CheckQuest(FName QuestKey) = 0;
	virtual void ChangeCamera(FName CameraName, float TransitionTime, bool bReenableDialogueAfterAnimation) = 0;
	virtual UObject* GetCurrentNode() = 0;
};
