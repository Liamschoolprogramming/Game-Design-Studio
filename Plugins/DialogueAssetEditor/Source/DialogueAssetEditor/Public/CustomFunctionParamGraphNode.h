// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionParamNodeBehaviour.h"
#include "CustomFunctionParamNodeInfo.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphNodeFactory.h"
#include "CustomFunctionParamGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UCustomFunctionParamGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()


	CREATE_GRAPH_NODE(
		FLinearColor::Blue,
		"CustomFunctionParamNode",
		UCustomFunctionParamNodeInfo,
		UCustomFunctionParamNodeBehaviour,
		false
	)
};
