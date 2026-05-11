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
	if (SlotIndex < 0) return;

	if (SlotIndex < PuzzleInventorySlots.Num())
	{
		// do not overwrite puzzle item of same type
		if (PuzzleItem.Name == PuzzleInventorySlots[SlotIndex].PuzzleInventoryItem.Name) return;
		
		// check if that slot has a puzzle item that is in-level
		// if so, it should be removed from level.
		FPuzzleInventorySlotItem ExistingPuzzleItemInSlot = PuzzleInventorySlots[SlotIndex];
		RemovePuzzleSlotElementFromLevel(SlotIndex);
		
		FPuzzleInventorySlotItem NewInventorySlotItem = FPuzzleInventorySlotItem(PuzzleItem, SlotIndex);
		PuzzleInventorySlots[SlotIndex] = NewInventorySlotItem;
	}
}

void UPuzzleInventoryManager::ClearPuzzleSlot(int index)
{
	if (index < PuzzleInventorySlots.Num())
	{
		RemovePuzzleSlotElementFromLevel(index);
		PuzzleInventorySlots[index] = FPuzzleInventorySlotItem();
	}
}

void UPuzzleInventoryManager::ClearPuzzleSlots()
{
	for (int i = 0; i < PuzzleInventorySlots.Num(); i++)
	{
		ClearPuzzleSlot(i);
	}
	
}

void UPuzzleInventoryManager::RemovePuzzleSlotElementFromLevel(int index)
{
	PuzzleInventorySlots[index].bInLevel = false;
	
	if (PuzzleInventorySlots[index].PuzzleItemRef != nullptr)
	{
		PuzzleInventorySlots[index].PuzzleItemRef->Destroy();
		PuzzleInventorySlots[index].PuzzleItemRef = nullptr;
	}
}

void UPuzzleInventoryManager::ResetAllPuzzleSlotsToNotInLevel()
{
	for (int i = 0; i < PuzzleInventorySlots.Num(); i++)
	{
		RemovePuzzleSlotElementFromLevel(i);
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
		if (PuzzleItem.PuzzleItemRef != nullptr)
		{
			
			APuzzleInteractive_Pickupable* PickupablePuzzleItem = Cast<APuzzleInteractive_Pickupable>(PuzzleItem.PuzzleItemRef);
			if (PickupablePuzzleItem != nullptr)
			{
				if (PickupablePuzzleItem->bHasActivatingElement)
				{
					// warn player on screen
					GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Cannot pickup activating element!");
					return;
				}
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
				// do not pickup a second object
				if (PlayerCharacter->PickupableObject) return;
				PickupablePuzzleItem->SetActorLocation(*(new FVector(PlayerCharacter->GetActorLocation().X + 10, PlayerCharacter->GetActorLocation().Y + 10, PlayerCharacter->GetActorLocation().Z)));
				PickupablePuzzleItem->Interact(PlayerCharacter);
			}
		}
	}
	else
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		// do not pickup a second object
		if (PlayerCharacter->PickupableObject) return;
		
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector Location(PlayerLocation.X + 30, PlayerLocation.Y + 30, PlayerLocation.Z);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		// spawn new puzzle element in level and attach to player
		APuzzle* PuzzleItemSpawned = GetWorld()->SpawnActor<APuzzle>(PuzzleItem.PuzzleInventoryItem.PuzzleItemClass, Location, Rotation, SpawnInfo);
		if (PuzzleItemSpawned == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not spawn puzzle actor!"));
			return;
		}
		
		PuzzleItemSpawned->SetInventorySlotIndex(index);

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

FPuzzleInventorySlotItem UPuzzleInventoryManager::GetPuzzleInventorySlotItem(int SlotIndex)
{
	if (SlotIndex < 0) return FPuzzleInventorySlotItem();
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