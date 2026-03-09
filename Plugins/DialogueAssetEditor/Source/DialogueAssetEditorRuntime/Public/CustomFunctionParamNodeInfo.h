// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfoBase.h"
#include "StructUtils/PropertyBag.h"
#include "CustomFunctionParamNodeInfo.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UCustomFunctionParamNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:
	//Properties go here
	
	UPROPERTY(EditAnywhere)
	FString FunctionName;
	
	UPROPERTY(EditAnywhere)
	FDialogueParameters Parameters;
};
