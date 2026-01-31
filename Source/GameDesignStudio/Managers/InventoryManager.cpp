// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"

void UInventoryManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerInventory = {};
	
	AllItems = {
		{"TestItem", FPlayerInventoryItem("Test Item", 0, 10)},
		{"AnotherTestItem", FPlayerInventoryItem("Another Test Item", 0, 15)},
	};
}

// tries to add an item to the inventory, returns true if success
// returns false if exceeded max amount or invalid item
bool UInventoryManager::AddToInventory(FName ItemName, int Amount)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);

	if (FoundItem == nullptr)
	{
		FPlayerInventoryItem* NewItem = AllItems.Find(ItemName);
		FPlayerInventoryItem ItemToAdd = FPlayerInventoryItem(NewItem->ItemDisplayName, Amount, NewItem->MaxAmount);
		
		if (NewItem == nullptr)
		{
			return false;
		}
		
		
		PlayerInventory.Add(ItemName, ItemToAdd);
		return true;
	}
	
	if ((FoundItem->CurrentAmount + Amount) > FoundItem->MaxAmount)
	{
		return false;
	}
	
	FoundItem-> CurrentAmount += Amount;
	return true;
}

bool UInventoryManager::RemoveFromInventory(FName ItemName, int Amount)
{
	return false;
}

void UInventoryManager::SetMaxAmountForItem(FName ItemName, int MaxAmount)
{
	
}

FPlayerInventoryItem UInventoryManager::GetItemDetails(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = AllItems.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return FPlayerInventoryItem();
	}
	return *FoundItem;
}

int UInventoryManager::GetCurrentAmountForItem(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = AllItems.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return 0;
	}
	return FoundItem->CurrentAmount;
}

