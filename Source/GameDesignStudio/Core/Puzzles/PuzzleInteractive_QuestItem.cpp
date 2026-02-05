
#include "PuzzleInteractive_QuestItem.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/InventoryManager.h"
#include "Managers/QuestManager.h"

void APuzzleInteractive_QuestItem::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!bPickedUp && PlayerCharacter->PlayerCharacterType == EPlayerCharacterType::Default)
	{
		bPickedUp = true;
		UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
		InventoryManager->AddToInventory(InventoryItemName, 1);
		
		Destroy();
	}
}

void APuzzleInteractive_QuestItem::BeginPlay()
{
	// check if activated on quest manager
	// if so, turn "on"
	UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager();
}
