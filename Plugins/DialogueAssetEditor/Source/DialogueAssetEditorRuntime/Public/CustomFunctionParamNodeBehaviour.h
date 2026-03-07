// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionParamNodeInfo.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfoBase.h"
#include "CustomFunctionParamNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UCustomFunctionParamNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()


	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UCustomFunctionParamNodeInfo* NodeInfo = Cast<UCustomFunctionParamNodeInfo>(NodeInfoBase);
		
		if (NodeInfo == nullptr) return;
		//Handler->CallCustomFunctionWithParams(NodeInfo->FunctionName, NodeInfo->Parameters);
	}
};
