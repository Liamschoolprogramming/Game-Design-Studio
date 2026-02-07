// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueActorComponent.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UDialogueActorComponent::UDialogueActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDialogueActorComponent::CreateWidgetAndAddToViewport()
{
	if (DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidgetBase>(GetWorld(), DialogueWidgetClass);
		DialogueWidget->AddToViewport();
		DialogueWidget->SetNPCName(NPCName);
	}
}

void UDialogueActorComponent::DestroyWidget()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
	}
}

// Called when the game starts
void UDialogueActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogueActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

