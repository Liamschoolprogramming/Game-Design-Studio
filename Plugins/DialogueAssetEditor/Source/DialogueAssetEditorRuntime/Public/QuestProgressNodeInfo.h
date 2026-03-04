// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "QuestNodeInfo.h"
#include "QuestProgressNodeInfo.generated.h"
/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UQuestProgressNodeInfo : public UQuestNodeInfo
{
	GENERATED_BODY()

public:
	//Properties go here
	

	UPROPERTY(EditAnywhere)
	FName SpeakerName;
	
	UPROPERTY(EditAnywhere)
	//Leave empty to use SpeakerName
	FName CameraName;
	
	UPROPERTY(EditAnywhere)
	// Will replace instances of $total and $current with the actual proper value from the quest manager
	FString Dialogue; 
	
	UPROPERTY(EditAnywhere)
	UTexture2D* CharacterPortrait;
};
