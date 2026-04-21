#pragma once

#include "CoreMinimal.h"
#include "Managers/PlayerStatManager.h"
#include "QuestData.generated.h"

UENUM(Blueprintable)
enum class EQuestState : uint8
{
	INACTIVE UMETA(DisplayName = "Inactive"),
	ACTIVE UMETA(DisplayName = "Active"),
	COMPLETED UMETA(DisplayName = "Completed"),
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FName QuestDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FString QuestSummary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FString QuestDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FName QuestItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int ItemAmountRequired;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	EQuestState QuestState;
	
	FQuest()
	{
		QuestState = EQuestState::INACTIVE;
		ItemAmountRequired = 0;
	}
	
	FQuest(FName QuestName, FString Summary, FString Description, FName ItemName, int RequiredAmount)
	{
		QuestState = EQuestState::INACTIVE;
		QuestDisplayName = QuestName;
		QuestSummary = Summary;
		QuestDescription = Description;
		QuestItem = ItemName;
		ItemAmountRequired = RequiredAmount;
	}
};
