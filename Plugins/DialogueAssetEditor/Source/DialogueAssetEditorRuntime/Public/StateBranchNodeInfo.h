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
	//Uses the tag property in the state, looks for exactly the tag. If we can't find the tag in the save
	TArray<FText> EditableStatesResponses;

	
	
	UPROPERTY()
	FText StartState = FText::FromString(TEXT("Not Started"));
	UPROPERTY()
	FText EndState = FText::FromString(TEXT("Finished"));
	
	
};
