
#include "PuzzleInteractive_QuestItem.h"

#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/InventoryManager.h"
#include "Managers/QuestManager.h"

void APuzzleInteractive_QuestItem::Interact(APlayerCharacter* PlayerCharacter)
{
	UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager();
	if (!QuestManager->IsQuestForItemActive(ItemName))
	{
		return;
	}
	
	if (!bPickedUp && PlayerCharacter->PlayerCharacterType == EPlayerCharacterType::Default)
	{
		bPickedUp = true;
		UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
		InventoryManager->AddToInventory(ItemName, 1);
		QuestManager->UpdateCompletionStatusForQuestItem(ItemName);
		
		Destroy();
	}
}

void APuzzleInteractive_QuestItem::BeginPlay()
{
	Super::BeginPlay();
	UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager();
	SetQuestItemActive(QuestManager->IsQuestForItemActive(ItemName));
}

void APuzzleInteractive_QuestItem::SetQuestItemActive_Implementation(bool Active) {}

