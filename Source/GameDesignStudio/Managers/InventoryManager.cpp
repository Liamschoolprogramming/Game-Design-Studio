// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryManager.h"

#include "InventoryInterface.h"
#include "QuestInterface.h"
#include "QuestManager.h"
#include "Blueprint/UserWidget.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

void UInventoryManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerInventory = {};
	
	AllItems = {
		//Quest Items
		{"Sunstone", FPlayerInventoryItem(
			"Sunstone",
			"A sunstone.",
			0, 10,
			EInventoryItemType::Quest
			)
		},
		{"Berry", FPlayerInventoryItem(
			"Berry",
			"A berry.",
			0, 10,
			EInventoryItemType::Quest
			)
		},
		{"Golem", FPlayerInventoryItem(
			"Golem",
			"A golem.",
			0, 1,
			EInventoryItemType::Quest,
			true
			)
		},
		{"OwlChild", FPlayerInventoryItem(
			"Owl Child",
			"One of Whistlebranch's children.",
			0, 4,
			EInventoryItemType::Quest
			)
		},
		
		//Gear
		{"AegisCharm", FPlayerInventoryItem(
			"Aegis Charm", 
			"A charm given to you by Verdan. Nullifies one instance of damage taken per life.",
			0, 1, 
			FGearInfo({{"Health",  5}}, {"DamageNullification"}, EGearType::Head)
			)
		},
		{"WindrunnerSandals", FPlayerInventoryItem(
			"Windrunner Sandals",
			"Sandals that you found in a chest. Grants +5 Stamina",
			0, 1, 
			FGearInfo({{"Stamina", 5}}, {}, EGearType::Legs)
			)
		},
	};
}

/**
 * Adds the given amount of the provided item to the player's inventory
 * @param ItemName
 * @param Amount
 * @return New amount in the player's inventory for the provided item
 */
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
		
		FPlayerInventoryItem ItemToAdd = FPlayerInventoryItem(NewItem->ItemDisplayName, NewItem->Description, Amount, NewItem->MaxAmount, NewItem->ItemType, NewItem->bHidden, NewItem->GearInfo);
		
		if (NewItem == nullptr)
		{
			return 0;
		}
		
		PlayerInventory.Add(ItemName, ItemToAdd);
		QuestManager->UpdateQuestProgress(ItemName);
		IInventoryInterface::Execute_OnItemAdded(InventoryMenu, ItemName);
		
		return Amount;
	}
	
	int Maximum = FoundItem->MaxAmount;
	if ((FoundItem->CurrentAmount + Amount) > Maximum)
	{
		FoundItem-> CurrentAmount = Maximum;
		QuestManager->UpdateQuestProgress(ItemName);
		IInventoryInterface::Execute_OnItemAdded(InventoryMenu, ItemName);
		
		return Maximum;
	}
	
	FoundItem-> CurrentAmount += Amount;
	QuestManager->UpdateQuestProgress(ItemName);
	IInventoryInterface::Execute_OnItemAdded(InventoryMenu, ItemName);
	
	return FoundItem-> CurrentAmount;
}

/**
 * Removes the given amount of the provided item from the player's inventory
 * @param ItemName
 * @param Amount
 * @return New amount in the player's inventory for the provided item
 */
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
		IInventoryInterface::Execute_OnItemRemoved(InventoryMenu, ItemName);
		
		return FoundItem-> CurrentAmount;
	}
	FoundItem->CurrentAmount = 0;
	QuestManager->UpdateQuestProgress(ItemName);
	IInventoryInterface::Execute_OnItemRemoved(InventoryMenu, ItemName);
	
	return 0;
}

/**
 * Sets the max amount of the provided item that the player can hold
 * @param ItemName
 * @param MaxAmount
 */
void UInventoryManager::SetMaxAmountForItem(FName ItemName, int MaxAmount)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);

	if (FoundItem != nullptr)
	{
		FoundItem->MaxAmount = MaxAmount;
	}
}

/**
 * @param ItemName
 * @return The PlayerInventoryItem Struct associated with the provided item name
 */
FPlayerInventoryItem UInventoryManager::GetItemDetails(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return FPlayerInventoryItem();
	}
	return *FoundItem;
}

/**
 * @param ItemName
 * @return The amount of the provided item in the player's inventory. -1 if the player has never obtained the item.
 */
int UInventoryManager::GetCurrentAmountForItem(FName ItemName)
{
	FPlayerInventoryItem* FoundItem = PlayerInventory.Find(ItemName);
	if (FoundItem == nullptr)
	{
		return 0;
	}
	return FoundItem->CurrentAmount;
}

