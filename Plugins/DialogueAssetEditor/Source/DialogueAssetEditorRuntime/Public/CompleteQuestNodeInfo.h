// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "CompleteQuestNodeInfo.generated.h"
/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UCompleteQuestNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:
	//Properties go here
	UPROPERTY(EditAnywhere)
	FName QuestName;
};
