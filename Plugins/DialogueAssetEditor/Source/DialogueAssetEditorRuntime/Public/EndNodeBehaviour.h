// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueNodeBehaviour.h"

#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "EndNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UEndNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UDialogueEndNodeInfo* EndNodeInfo = Cast<UDialogueEndNodeInfo>(NodeInfoBase);
		if (!EndNodeInfo) return;
		
		
		Handler->EndDialogue(EndNodeInfo->Action, EndNodeInfo->ActionData);
		
	}
};
