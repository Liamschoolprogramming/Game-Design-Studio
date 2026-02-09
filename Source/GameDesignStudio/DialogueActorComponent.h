// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueWidgetBase.h"
#include "Components/ActorComponent.h"
#include "DialogueActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDESIGNSTUDIO_API UDialogueActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueActorComponent();
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UDialogueWidgetBase> DialogueWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category="UI")
	UDialogueWidgetBase* DialogueWidget;
	
	UPROPERTY(BlueprintReadWrite, Category="Dialogue")
	FText NPCName = FText::FromString(TEXT("NPC Name"));
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateWidgetAndAddToViewport();
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DestroyWidget();
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
