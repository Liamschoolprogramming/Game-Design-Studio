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
		FDialogueAudio Sound;
		float Speed = 3.5;
		if (NodeInfo->DialogueOptions.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, NodeInfo->DialogueOptions.Num() - 1);
			
			DialogueText = NodeInfo->DialogueOptions[RandomIndex];
			if (NodeInfo->AudioOptions.IsValidIndex(RandomIndex))
			{
				Sound = NodeInfo->AudioOptions[RandomIndex];
			}
			if (NodeInfo->DialogueSpeedOptions.IsValidIndex(RandomIndex))
			{
				Speed = NodeInfo->DialogueSpeedOptions[RandomIndex];
			}
			
		}
		
		Handler->SetDialogueText(DialogueText, Speed);
		Handler->PlayAudio(Sound);
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
