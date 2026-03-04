// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "StateBranchNodeInfo.generated.h"



/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UStateBranchNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:
	//Properties go here
	UPROPERTY(EditAnywhere, DisplayName= "States")
	TArray<FText> EditableStatesResponses;
	
	UPROPERTY()
	FText StartState = FText::FromString(TEXT("FirstTime"));
	
	
};
