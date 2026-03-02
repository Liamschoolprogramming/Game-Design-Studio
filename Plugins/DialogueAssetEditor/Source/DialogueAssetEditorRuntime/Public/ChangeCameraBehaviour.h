// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeCameraNodeInfo.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueMacros.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "ChangeCameraBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UChangeCameraBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UChangeCameraNodeInfo* NodeInfo = Cast<UChangeCameraNodeInfo>(NodeInfoBase);
		UDialogueRuntimeNode* CurrentNode = Cast<UDialogueRuntimeNode>(Handler->GetCurrentNode());
		
		if (UDialogueeRuntimePin* OutputPin = CurrentNode->OutputPins[0]; OutputPin->Connection != nullptr)
		{
			CurrentNode = OutputPin->Connection->Parent;
		}
		else
		{
			//no connection so we assume it's an end node
			CurrentNode = nullptr;
		}
		if (CurrentNode != nullptr)
		{
			if (CurrentNode->NodeType == "EndNode")
			{
				CurrentNode = nullptr;
			}
		}
		if (CurrentNode)
		{
			Handler->ChangeCamera(NodeInfo->CameraName, NodeInfo->TransitionTime, true);
		}
		else
		{
			Handler->ChangeCamera(NodeInfo->CameraName, NodeInfo->TransitionTime, false);
		}
		
	}
	
	
};
