// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "StateBranchNodeInfo.h"
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
		UStateBranchNodeInfo* NodeInfo = Cast<UStateBranchNodeInfo>(NodeInfoBase);
		UE_LOG(LogTemp, Error, TEXT("Checking Asset"));
		if (UDialogueAsset* Asset =Handler->GetAsset())
		{
			UE_LOG(LogTemp, Error, TEXT("Checking Subsystem"));
			if (UDialogueSubsystem* DialogueSubsystem =  Handler->GetWorldFromPlayer()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>())
			{
				
				Handler->CheckDialogueState();
			}
		}
	}
};
