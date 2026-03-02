// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueNodeInfo.h"
#include "DialogueExecutionHandler.h"
#include "QuestNodeInfo.h"
#include "StartQuestBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UStartQuestBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UQuestNodeInfo* QuestNodeInfo = Cast<UQuestNodeInfo>(NodeInfoBase);
		if (!QuestNodeInfo) return;
		
		Handler->StartQuest(QuestNodeInfo->QuestName);
	}
};
