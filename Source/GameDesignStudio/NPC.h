// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueActorComponent.h"
#include "PlayerCharacter.h"
#include "NPC.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API ANPC : public APlayerCharacter
{
	GENERATED_BODY()
	
	
public:
	ANPC();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UDialogueActorComponent* DialogueActorComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialogue")
	FText NPCName = FText::FromString(TEXT("Deafult NPC Name"));
};
