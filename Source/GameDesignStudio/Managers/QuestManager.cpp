// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include <string>

#include "InventoryManager.h"
#include "PlayerStatManager.h"
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
				EPlayerBoostableStat::Mind,
				5,
				"None"
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
				10,
				"None"
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
				EPlayerBoostableStat::Stamina,
				3,
				"None"
			)
		},
	};
	
	// testing only
	//ActivateQuestForItem("Golem");
}

//Starts the given quest
void UQuestManager::ActivateQuestForItem(FName ItemName)
{
	FQuest* FoundQuest = Quests.Find(ItemName);
	if (FoundQuest != nullptr)
	{
		FoundQuest->QuestState = EQuestState::ACTIVE;
		if (QuestMenu != nullptr)
		{
			IQuestInterface::Execute_OnQuestStarted(QuestMenu, ItemName);
		}
		
		UpdateCompletionStatusForQuestItem(ItemName);
	}
}

void UQuestManager::UpdateCompletionStatusForQuestItem(FName ItemName)
{
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
	
	if (InventoryManager->GetCurrentAmountForItem(ItemName) >= RequiredAmount)
	{
		Quest->QuestState = EQuestState::COMPLETED;
		InventoryManager->RemoveFromInventory(ItemName, RequiredAmount);
		ProvideReward(ItemName);
		
		IQuestInterface::Execute_OnQuestCompleted(QuestMenu, ItemName);
	}
	
	IQuestInterface::Execute_OnQuestProgressChanged(QuestMenu, ItemName);
}

//Provides player with rewards for given quest
void UQuestManager::ProvideReward(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return;
	}
	
	if (Quest->QuestState != EQuestState::COMPLETED)
	{
		return;
	}
	
	if (Quest->StatRewardAmount != 0)
	{
		UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
		
		PlayerStatManager->BoostPlayerStat(Quest->StatReward, Quest->StatRewardAmount);
	}
	
	if (Quest->GearReward != "None")
	{
		UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
		
		//add gear here
	}
}

//Returns whether the given quest's state is active.
//Will not return true if quest is Completed.
bool UQuestManager::IsQuestForItemActive(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}

	return (Quest->QuestState == EQuestState::ACTIVE);
}

//Returns state of the given quest
//Returns Inactive if the quest is invalid.
EQuestState UQuestManager::GetQuestState(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return EQuestState::INACTIVE;
	}
	return Quest->QuestState;
}
