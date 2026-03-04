// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "StateSwitchNodeBehaviour.generated.h"



/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UStateSwitchNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		//Behaviour here
		
		//TODO Box only
		/**
		 * We want to check a Dialogue Subsystem here
		 * need to store states as a asset reference mapped to Enum of states (NotStarted, Finished, FinishedWithTag) as wll as a Tag tied to the asset
		 * Probably a struct
		 * 
		 * struct 
		* 
		* 
UENUM()
enum EStates
{
	NotStarted,
	Finished,
	FinishedWithTag
};
		* 
USTRUCT()
struct FStateData
{
	EStates State;
	
	FText Tag;
	
};
		 */
	}
};
