// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInventoryManager.h"
#include "Macros.h"

UPuzzleInventoryManager::UPuzzleInventoryManager()
{
	PuzzleInventorySlots = TArray<FPuzzleInventorySlotItem>();
	for (int i = 0; i < MaxSlots; i++)
	{
		PuzzleInventorySlots.Add(FPuzzleInventorySlotItem(i));
	}
}

void UPuzzleInventoryManager::UnlockPuzzleItem(FPuzzleInventoryItem PuzzleItem)
{
	// do not add duplicate items
	for (int i = 0; i < PuzzleItems.Num(); i++)
	{
		if (PuzzleItems[i].Name == PuzzleItem.Name)
		{
			return;
		}
	}
	PuzzleItems.Add(PuzzleItem);
}

void UPuzzleInventoryManager::SetPuzzleSlot(FPuzzleInventoryItem PuzzleItem, int SlotIndex)
{

	if (SlotIndex < PuzzleInventorySlots.Num())
	{
		// do not overwrite puzzle item of same type
		if (PuzzleItem.Name == PuzzleInventorySlots[SlotIndex].PuzzleInventoryItem.Name) return;
		
		// check if that slot has a puzzle item that is in-level
		// if so, it should be removed from level.
		FPuzzleInventorySlotItem ExistingPuzzleItemInSlot = PuzzleInventorySlots[SlotIndex];
		if (ExistingPuzzleItemInSlot.bInLevel)
		{
			ExistingPuzzleItemInSlot.PuzzleItemRef->Destroy();
		}
		
		FPuzzleInventorySlotItem NewInventorySlotItem = FPuzzleInventorySlotItem(PuzzleItem, SlotIndex);
		PuzzleInventorySlots[SlotIndex] = NewInventorySlotItem;
	}
}

void UPuzzleInventoryManager::ClearPuzzleSlots()
{
	PuzzleInventorySlots = TArray<FPuzzleInventorySlotItem>();
}

void UPuzzleInventoryManager::ResetAllPuzzleSlotsToNotInLevel()
{
	for (int i = 0; i < PuzzleInventorySlots.Num(); i++)
	{
		PuzzleInventorySlots[i].bInLevel = false;
	}
}

int UPuzzleInventoryManager::GetMaxSlots()
{
	return MaxSlots;	
}

void UPuzzleInventoryManager::AddPuzzleInventorySlot()
{
	MaxSlots++;
	PuzzleInventorySlots.Add(FPuzzleInventorySlotItem(PuzzleInventorySlots.Num()));
}

void UPuzzleInventoryManager::PickupPuzzleItem_Implementation(APuzzle* PuzzleItem)
{
	// check if is in level 
	// if not then instantiate and attach to player
	
	// get player hold item location 
	// FVector Location(0.0f, 0.0f, 0.0f);
	// FRotator Rotation(0.0f, 0.0f, 0.0f);
	// FActorSpawnParameters SpawnInfo;
	// GetWorld()->SpawnActor<APuzzle>(
	// PuzzleItemToSpawn.PuzzleInventoryItem.PuzzleItemClass, Location, Rotation, SpawnInfo);
	//PuzzleInventorySlots[SlotIndex].PuzzleItemRef = 
	
	if (PuzzleItem != nullptr)
	{
		int PuzzleItemSlotIndex = PuzzleItem->GetInventorySlotIndex();
		if (PuzzleInventorySlots.Num() > PuzzleItemSlotIndex && PuzzleInventorySlots[PuzzleItemSlotIndex].bInLevel)
		{
			UE_LOG(LogTemp, Warning, TEXT("IS IN LEVEL"));
		}
	}
}

FPuzzleInventorySlotItem UPuzzleInventoryManager::GetPuzzleInventorySlotItem(int SlotIndex)
{
	return PuzzleInventorySlots[SlotIndex];
}

TArray<FPuzzleInventorySlotItem> UPuzzleInventoryManager::GetPuzzleInventorySlots()
{
	return PuzzleInventorySlots;
}

TArray<FPuzzleInventoryItem> UPuzzleInventoryManager::GetAvailablePuzzleItems()
{
	return PuzzleItems;
}