// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueSpeakerComponent.h"
#include "UObject/Interface.h"
#include "DialogueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class GAMEDESIGNSTUDIO_API UDialogueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEDESIGNSTUDIO_API IDialogueInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDialogueSpeakerComponent* GetSpeakerComponent() const;
};
