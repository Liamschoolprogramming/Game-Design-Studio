// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueAudio.h"
#include "DialogueNodeInfo.h"
#include "DialogueNodeInfoBase.h"
#include "UObject/Object.h"
#include "RandomDialogueNodeInfo.generated.h"

/**
 * 
 */
UCLASS(HideCategories=("DialogueText"))
class DIALOGUEASSETEDITORRUNTIME_API URandomDialogueNodeInfo : public UDialogueNodeInfo
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueOptions;
	
	UPROPERTY(EditAnywhere)
	//line will play at the same index as the dialogue text
	TArray<FDialogueAudio> AudioOptions;
	
	UPROPERTY(EditAnywhere)
	//bigger means faster
	TArray<float> DialogueSpeedOptions;
	
	
	
};
