// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfoBase.h"
#include "UObject/Object.h"
#include "DialogueNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueNodeBehaviour : public UObject
{
	GENERATED_BODY()
	
	public:
	virtual void Execute(UDialogueNodeInfoBase* DialogueNodeInfo, IDialogueExecutionHandler* Handler)  {};
	
	
	
	
};
