// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"

#include "QuestInterface.h"
#include "QuestManager.h"
#include "Blueprint/UserWidget.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

void UInventoryManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerInventory = {};
	
	AllItems = {
		{"TestItem", FPlayerInventoryItem("Test Item", 0, 10, EInventoryItemType::Quest, false)},
		{"AnotherTestItem", FPlayerInventoryItem("Another Test Item", 0, 15, EInventoryItemType::Quest, false)},
		{"Sunstone", FPlayerInventoryItem("Sunstone", 0, 10, EInventoryItemType::Quest, false)},
		{"Golem", FPlayerInventoryItem("Golem", 0, 1, EInventoryItemType::Quest, true)},
		{"Owl Child", FPlayerInventoryItem("Owl Child", 0, 4, EInventoryItemType::Quest, false)},
	};
}

// Tries to add an item to the inventory, returns new amount in inventory for that item.
int UInventoryManager::AddToInventory(FName ItemName, int Amount)
{
	if (ItemName ==  NAME_None)
	{
		return -1;
	}
	
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);
	UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager();
	
	//Add Item
	if (FoundItem == nullptr)
	{
		FPlayerInventoryItem* NewItem = AllItems.Find(ItemName);
		
		FPlayerInventoryItem ItemToAdd = FPlayerInventoryItem(NewItem->ItemDisplayName, Amount, NewItem->MaxAmount, EInventoryItemType::Quest, NewItem->Hidden);
		
		if (NewItem == nullptr)
		{
			return 0;
		}
		
		PlayerInventory.Add(ItemName, ItemToAdd);
		QuestManager->UpdateQuestProgress(ItemName);
		
		return Amount;
	}
	
	int Maximum = FoundItem->MaxAmount;
	if ((FoundItem->CurrentAmount + Amount) > Maximum)
	{
		FoundItem-> CurrentAmount = Maximum;
		QuestManager->UpdateQuestProgress(ItemName);
		
		return Maximum;
	}
	
	FoundItem-> CurrentAmount += Amount;
	QuestManager->UpdateQuestProgress(ItemName);
	
	return FoundItem-> CurrentAmount;
}

// Tries to remove a specified amount of a given item from the inventory
// and returns the new integer amount in inventory for that item.
int UInventoryManager::RemoveFromInventory(FName ItemName, int Amount)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);

	if (FoundItem == nullptr)
	{
		return 0;
	}
	
	UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager();
	
	if (FoundItem->CurrentAmount >= Amount)
	{
		FoundItem-> CurrentAmount -= Amount;
		QuestManager->UpdateQuestProgress(ItemName);
		return FoundItem-> CurrentAmount;
	}
	FoundItem->CurrentAmount = 0;
	QuestManager->UpdateQuestProgress(ItemName);
	return 0;
}

void UInventoryManager::SetMaxAmountForItem(FName ItemName, int MaxAmount)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);

	if (FoundItem != nullptr)
	{
		FoundItem->MaxAmount = MaxAmount;
	}
}

FPlayerInventoryItem UInventoryManager::GetItemDetails(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return FPlayerInventoryItem();
	}
	return *FoundItem;
}

int UInventoryManager::GetCurrentAmountForItem(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return 0;
	}
	return FoundItem->CurrentAmount;
}

