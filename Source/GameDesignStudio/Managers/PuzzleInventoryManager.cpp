// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInventoryManager.h"
#include "Macros.h"
#include "Core/Puzzles/Pickups/PuzzleInteractive_Pickupable.h"
#include "Kismet/GameplayStatics.h"

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

void UPuzzleInventoryManager::PlacePuzzleItemInLevel(int index)
{
	if (index >= PuzzleInventorySlots.Num()) return;
	
	FPuzzleInventorySlotItem PuzzleItem = PuzzleInventorySlots[index];
	if (PuzzleItem.bInLevel)
	{
		// snap position of puzzle ref to player pickup point
		// and set player to holding item
		// they can they use E as normal to place down
		// and B to put back in inventory
		// use PuzzleInteractive_Pickupable functions
		if (PuzzleItem.PuzzleItemRef != nullptr)
		{
			APuzzleInteractive_Pickupable* PickupablePuzzleItem = Cast<APuzzleInteractive_Pickupable>(PuzzleItem.PuzzleItemRef);
			if (PickupablePuzzleItem != nullptr)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
				PickupablePuzzleItem->SetActorLocation(*(new FVector(PlayerCharacter->GetActorLocation().X + 10, PlayerCharacter->GetActorLocation().Y + 10, PlayerCharacter->GetActorLocation().Z)));
				PickupablePuzzleItem->Interact(PlayerCharacter);
			}
		}
	}
	else
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector Location(PlayerLocation.X + 10, PlayerLocation.Y + 10, PlayerLocation.Z);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		// spawn new puzzle element in level and attach to player
		APuzzle* PuzzleItemSpawned = GetWorld()->SpawnActor<APuzzle>(PuzzleItem.PuzzleInventoryItem.PuzzleItemClass, Location, Rotation, SpawnInfo);
		PuzzleItemSpawned->OwningManager = UPuzzleRiverManager::StaticClass();
		APuzzleInteractive_Pickupable* PickupablePuzzleItem = Cast<APuzzleInteractive_Pickupable>(PuzzleItemSpawned);
		if (PickupablePuzzleItem != nullptr)
		{
			PickupablePuzzleItem->SetActorLocation(*(new FVector(PlayerCharacter->GetActorLocation().X + 10, PlayerCharacter->GetActorLocation().Y + 10, PlayerCharacter->GetActorLocation().Z)));
			PickupablePuzzleItem->Interact(PlayerCharacter);
		}

		// update slot info
		PuzzleInventorySlots[index].bInLevel = true;
		PuzzleInventorySlots[index].PuzzleItemRef = PuzzleItemSpawned;
	}
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