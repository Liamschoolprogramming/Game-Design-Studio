// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "InventoryManager.h"
#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Data/PlayerStats.h"

void UQuestManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	Quests = {
		{"TestItem", FQuest("Test Quest", "TestItem", 10)},
		{"AnotherTestItem", FQuest("Test Quest", "TestItem", 10)},
	};
	
	// testing only
	ActivateQuestForItem("TestItem");
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