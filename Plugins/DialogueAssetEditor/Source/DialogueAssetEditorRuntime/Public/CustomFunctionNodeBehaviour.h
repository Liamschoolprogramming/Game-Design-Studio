// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionNodeInfo.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "CustomFunctionNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UCustomFunctionNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UCustomFunctionNodeInfo* NodeInfo = Cast<UCustomFunctionNodeInfo>(NodeInfoBase);
		if (NodeInfo == nullptr) return;
		Handler->CallCustomFunction(NodeInfo->FunctionName);
	}
};
