// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionNodeBehaviour.h"
#include "CustomFunctionNodeInfo.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphNodeFactory.h"

#include "CustomFunctionGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UCustomFunctionGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

	CREATE_GRAPH_NODE(FLinearColor::Blue,"CustomFunctionGraphNode", UCustomFunctionNodeInfo, UCustomFunctionNodeBehaviour, false)
protected:
	UPROPERTY()
	class UCustomFunctionNodeBehaviour* NodeBehaviour = nullptr;
	UPROPERTY()
	class UCustomFunctionNodeInfo* NodeInfo = nullptr;
};
