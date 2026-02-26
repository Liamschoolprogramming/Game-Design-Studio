// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "UObject/Object.h"
#include "DialogueCheckQuestNodeInfo.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueCheckQuestNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()
	
public:
	

	UPROPERTY(EditAnywhere)
	FName QuestName;
	
	
};
