// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "InventoryManager.h"
#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

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
				1
			)
		},
		//Night Quest - Stoneface
		{
			"Golem",
			FQuest(
				"Self-Aware Golem",
				"The Golem wants someone to talk to.",
				"Golem",
				1
			)
		},
		//Lehan Quest - Whistlebranch
		{
			"Owl Child",
			FQuest(
				"Whistlebranch's Missing Children",
				"Whistlebranch can't seem to find her children. Help her find them.",
				"Owl Child",
				4
			)
		},
	};
	
	// testing only
	ActivateQuestForItem("Golem");
}

void UQuestManager::ActivateQuestForItem(FName ItemName)
{
	FQuest* FoundQuest = Quests.Find(ItemName);
	if (FoundQuest != nullptr)
	{
		FoundQuest->Active = true;
	}
	
	
}

void UQuestManager::UpdateCompletionStatusForQuestItem(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return;
	}
	
	int RequiredAmount = Quest->ItemAmountRequired;
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	
	if (InventoryManager->GetCurrentAmountForItem(ItemName) >= RequiredAmount)
	{
		Quest->Completed = true;
	}
}

bool UQuestManager::IsQuestForItemActive(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}

	return (Quest->Active);
}