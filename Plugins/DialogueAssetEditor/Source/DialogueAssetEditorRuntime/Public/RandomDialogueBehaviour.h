// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueNodeInfo.h"
#include "DialogueExecutionHandler.h"
#include "RandomDialogueNodeInfo.h"
#include "RandomDialogueBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API URandomDialogueBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		URandomDialogueNodeInfo* NodeInfo = Cast<URandomDialogueNodeInfo>(NodeInfoBase);
		if (!NodeInfo) return;
		
		
		
		//pick a random line from responses
		FText DialogueText;
		if (NodeInfo->DialogueOptions.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, NodeInfo->DialogueOptions.Num() - 1);
			
			DialogueText = NodeInfo->DialogueOptions[RandomIndex];
		}
		
		Handler->SetDialogueText(DialogueText);
		Handler->ClearResponses();
    
		int OptionIndex = 0;
		for (FText Response : NodeInfo->DialogueResponses)
		{
			Handler->AddResponseButton(Response, OptionIndex);
			OptionIndex++;
		}
		Handler->SetupCameraAndSpeaker(NodeInfo->CameraName, NodeInfo->SpeakerName, NodeInfo->CharacterPortrait);
	}
};
