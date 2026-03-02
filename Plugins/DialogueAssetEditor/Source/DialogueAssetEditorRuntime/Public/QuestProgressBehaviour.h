// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueNodeInfo.h"
#include "QuestProgressNodeInfo.h"
#include "DialogueExecutionHandler.h"
#include "QuestProgressBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UQuestProgressBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		
		UQuestProgressNodeInfo* NodeInfo = Cast<UQuestProgressNodeInfo>(NodeInfoBase);
		
		TArray<int> Progress = Handler->GetQuestProgress(NodeInfo->QuestName);
		
		FString DialogueText;
		if (NodeInfo->Dialogue != TEXT(""))
		{
			DialogueText = NodeInfo->Dialogue;
			
					
			DialogueText = DialogueText.Replace(TEXT("$total"), *FString::FromInt(Progress[1]));
			DialogueText = DialogueText.Replace(TEXT("$current"), *FString::FromInt(Progress[0]));

					
		}
		
		Handler->SetDialogueText(FText::FromString(DialogueText));
		Handler->ClearResponses();
		Handler->AddResponseButton(FText::FromString(TEXT("Continue")),0);
				
				
			
				
	}
};
