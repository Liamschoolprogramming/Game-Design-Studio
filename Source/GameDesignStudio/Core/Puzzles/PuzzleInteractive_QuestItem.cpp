
#include "PuzzleInteractive_QuestItem.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/InventoryManager.h"

void APuzzleInteractive_QuestItem::Interact(APlayerCharacter* PlayerCharacter)
{
	UInventoryManager* InventoryManager = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	InventoryManager->AddToInventory(InventoryItemName, 1);
	
	Destroy();
}
