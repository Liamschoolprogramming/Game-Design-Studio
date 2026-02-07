// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DialogueWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UDialogueWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dialogue")
	FText NPCName = FText::FromString(TEXT("NPC Name"));
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dialogue")
	FText DialogueText = FText::FromString(TEXT("This is an example of dialogue"));
	
	UPROPERTY(meta = (BindWidget))
	UImage* NPCPortraitImage;
	
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetNPCName(FText NameIn);
	
	UFUNCTION(BlueprintCallable, Category="UI")
	void SetDialogueText(FText NewDialogueText);
	
	
	
};
