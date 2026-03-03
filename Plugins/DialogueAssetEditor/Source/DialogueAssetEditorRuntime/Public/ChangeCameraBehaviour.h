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
		UE_LOG(LogTemp, Error, TEXT("EXECUTE CHANGE CAMERA"));
		if (UDialogueeRuntimePin* OutputPin = CurrentNode->OutputPins[0]; OutputPin->Connection != nullptr)
		{
			CurrentNode = OutputPin->Connection->Parent;
			UE_LOG(LogTemp, Error, TEXT("Found a connection"));
		}
		else
		{
			//no connection so we assume it's an end node
			UE_LOG(LogTemp, Display, TEXT("No node connection found"));
			CurrentNode = nullptr;
		}
		if (CurrentNode != nullptr)
		{
			if (CurrentNode->NodeType == "EndNode")
			{
				UE_LOG(LogTemp, Display, TEXT("End node found"));
				CurrentNode = nullptr;
			}
		}
		if (CurrentNode)
		{
			UE_LOG(LogTemp, Display, TEXT("We have more afterwards"));
			Handler->ChangeCamera(NodeInfo->CameraName, NodeInfo->TransitionTime, true);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("we are ending afterwards"));
			Handler->ChangeCamera(NodeInfo->CameraName, NodeInfo->TransitionTime, false);
		}
		
	}
	
	
};
