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
}

/**
 * Starts quest for the provided Item
 * @param ItemName 
 */
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
		
		UpdateQuestProgress(ItemName);
	}
}

/**
 * Updates progress on quest
 * @param ItemName 
 */
void UQuestManager::UpdateQuestProgress(FName ItemName)
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
	
	IQuestInterface::Execute_OnQuestProgressChanged(QuestMenu, ItemName);
}


/**
 * 
 * @param ItemName 
 * @return Array with the amount of items the player has at index 0 and the amount they need at index 1. {-1, -1} if the quest is invalid
 */
TArray<int> UQuestManager::GetQuestProgress(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return {-1, -1};
	}
	
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	int CurrentAmount = InventoryManager->GetCurrentAmountForItem(ItemName);
	
	return {CurrentAmount, Quest->ItemAmountRequired};
}

/**
 * 
 * @param ItemName 
 * @return whether the given quest can be completed
 */
bool UQuestManager::CanCompleteQuest(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}
	if (Quest->QuestState != EQuestState::ACTIVE)
	{
		return false;
	}
	
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	return (InventoryManager->GetCurrentAmountForItem(ItemName) >= Quest->ItemAmountRequired);
}

/**
 * Completes the given quest if requirements are fulfilled
 * @param ItemName
 * @return whether the quest was completed successfully
 */
bool UQuestManager::CompleteQuest(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}
	if (Quest->QuestState != EQuestState::ACTIVE)
	{
		return false;
	}
	
	int RequiredAmount = Quest->ItemAmountRequired;
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	if (InventoryManager->GetCurrentAmountForItem(ItemName) >= RequiredAmount)
	{
		Quest->QuestState = EQuestState::COMPLETED;
		UpdateQuestProgress(ItemName);
		
		InventoryManager->RemoveFromInventory(ItemName, RequiredAmount);
		ProvideReward(ItemName);
		
		IQuestInterface::Execute_OnQuestCompleted(QuestMenu, ItemName);
		return true;
	}
	return false;
}

/**
 * Provides player with rewards for given quest
 * @param ItemName
 */
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
		//UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
		//add gear here
	}
}

/**
 * 
 * @param ItemName
 * @return whether the given quest is Active. Will not return true if quest is Completed
 */
bool UQuestManager::IsQuestForItemActive(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return false;
	}

	return (Quest->QuestState == EQuestState::ACTIVE);
}

/**
 * 
 * @param ItemName
 * @return state of the given quest
 */
EQuestState UQuestManager::GetQuestState(FName ItemName)
{
	FQuest* Quest = Quests.Find(ItemName);
	if (Quest == nullptr)
	{
		return EQuestState::INACTIVE;
	}
	return Quest->QuestState;
}
