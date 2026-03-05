// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphNodeFactory.h"
#include "StateBranchNodeInfo.h"
#include "StateSwitchNodeBehaviour.h"
#include "StateSwitchGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UStateSwitchGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()


	CREATE_GRAPH_NODE(
		FLinearColor::Blue,
	    "StateSwitchNode",
		UStateBranchNodeInfo,
		UStateSwitchNodeBehaviour,
	    true
	)
};
