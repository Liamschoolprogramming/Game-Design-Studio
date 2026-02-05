// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "Macros.h"
#include "Data/PlayerStats.h"

void UQuestManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Debug::PrintToScreen(("UQuestManager::Initialize()"));
	Super::Initialize(InstanceOwner);
	
	Quests = {
		{"TestItem", FQuest("Test Quest", "TestItem", 10)},
		{"AnotherTestItem", FQuest("Test Quest", "TestItem", 10)},
	};
	
	// testing only
	ActivateQuest("TestItem");
}

void UQuestManager::ActivateQuest(FName ItemName)
{
	FQuest* FoundQuest = Quests.Find(ItemName);
	if (FoundQuest != nullptr)
	{
		FoundQuest->Active = true;
	}
}

bool UQuestManager::IsQuestForItemActive(FName ItemName)
{
	Debug::PrintToScreen((ItemName));
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}

	return (Quest->Active);
}