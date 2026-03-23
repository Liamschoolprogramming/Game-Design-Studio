// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInventoryManager.h"
#include "Macros.h"

APuzzleInventoryManager::APuzzleInventoryManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PuzzleInventorySlots = TArray<FPuzzleInventorySlotItem>();
}

void APuzzleInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleInventoryManager::UnlockPuzzleItem(FPuzzleInventoryItem PuzzleItem)
{
	PuzzleItems.Add(PuzzleItem);
}

void APuzzleInventoryManager::SetPuzzleSlot(FPuzzleInventoryItem PuzzleItem, int SlotIndex)
{

	if (SlotIndex < PuzzleItems.Num())
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
		
		PuzzleItems[SlotIndex] = PuzzleItem;
	}
}

void APuzzleInventoryManager::ClearPuzzleSlots()
{
	PuzzleInventorySlots = TArray<FPuzzleInventorySlotItem>();
}

void APuzzleInventoryManager::AddPuzzleInventorySlot()
{
	MaxSlots++;
}

void APuzzleInventoryManager::PickupPuzzleItem_Implementation(APuzzle* PuzzleItem)
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

FPuzzleInventorySlotItem APuzzleInventoryManager::GetPuzzleInventorySlotItem(int SlotIndex)
{
	return PuzzleInventorySlots[SlotIndex];
}
