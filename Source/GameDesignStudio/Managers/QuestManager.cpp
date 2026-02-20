// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include <string>

#include "InventoryManager.h"
#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/QuestInterface.h"
#include "Blueprint/UserWidget.h"
#include "Engine/RendererSettings.h"

void UQuestManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	Quests = {
		//Day Quest - Sundew
		{
			"Sunstone",
			FQuest(
				"Flower Spirit Sundew",
				"A cheery sunflower spirit wants to live closer to the goddess but it's too cold. Find a Sunstone to heat up its living space.",
				"Sunstone",
				1,
				EPlayerBoostableStat::Health,
				0
			)
		},
		//Night Quest - Stoneface
		{
			"Golem",
			FQuest(
				"Self-Aware Golem",
				"The Golem wants someone to talk to.",
				"Golem",
				1,
				EPlayerBoostableStat::Health,
				0
			)
		},
		//Lehan Quest - Whistlebranch
		{
			"Owl Child",
			FQuest(
				"Whistlebranch's Missing Children",
				"Whistlebranch can't seem to find her children. Help her find them.",
				"Owl Child",
				4,
				EPlayerBoostableStat::Health,
				0
			)
		},
	};
	
	// testing only
	//ActivateQuestForItem("Golem");
}

void UQuestManager::ActivateQuestForItem(FName ItemName)
{
	FQuest* FoundQuest = Quests.Find(ItemName);
	if (FoundQuest != nullptr)
	{
		FoundQuest->QuestState = EQuestState::ACTIVE;
		if (QuestMenu != nullptr)
		{
			IQuestInterface::Execute_QuestStarted(QuestMenu, ItemName);
		}
	}
	
	
}

void UQuestManager::UpdateCompletionStatusForQuestItem(FName ItemName)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, ItemName.ToString());
	
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return;
	}
	
	if (Quest->QuestState != EQuestState::ACTIVE)
	{
		return;
	}
	
	int RequiredAmount = Quest->ItemAmountRequired;
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	
	//This is always returning 0 for some reason??
	if (GEngine) {
		int InvAmount =  InventoryManager->GetCurrentAmountForItem(ItemName);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(InvAmount));
	}
	
	if (InventoryManager->GetCurrentAmountForItem(ItemName) >= RequiredAmount)
	{
		Quest->QuestState = EQuestState::COMPLETED;
		InventoryManager->RemoveFromInventory(ItemName, RequiredAmount);
		IQuestInterface::Execute_QuestCompleted(QuestMenu, ItemName);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Completed");
	}
}

bool UQuestManager::IsQuestForItemActive(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}

	return (Quest->QuestState == EQuestState::ACTIVE);
}

EQuestState UQuestManager::GetQuestState(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return EQuestState::INACTIVE;
	}
	return Quest->QuestState;
}
