// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueNodeBehaviour.h"

#include "DialogueSharedTypes.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "DialogueSubsystem.h"
#include "EndNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UEndNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UDialogueEndNodeInfo* EndNodeInfo = Cast<UDialogueEndNodeInfo>(NodeInfoBase);
		if (!EndNodeInfo) return;

		if (UDialogueSubsystem* DialogueSubsystem =  Handler->GetWorldFromPlayer()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>())
		{
			const TSoftObjectPtr<UDialogueAsset> AssetPtr = Handler->GetAsset();
			if (AssetPtr.IsValid())
			{
				UE_LOG(LogTemp, Display, TEXT("Valid"));
			}else
			{
				UE_LOG(LogTemp, Display, TEXT("Invalid"));
			}
			const FStateData Data = FStateData(EndNodeInfo->EndState, EndNodeInfo->EndStateTag);
			DialogueSubsystem->RegisterStateData(AssetPtr, Data);
		}
		
		
		Handler->EndDialogue();
		
	}
};
