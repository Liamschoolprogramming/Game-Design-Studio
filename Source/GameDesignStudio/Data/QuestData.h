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
	FName QuestSummary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FName QuestItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int ItemAmountRequired;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	EQuestState QuestState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	EPlayerBoostableStat StatReward;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	double StatRewardAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FName GearReward;
	
	FQuest()
	{
		QuestState = EQuestState::INACTIVE;
		ItemAmountRequired = 0;
		StatReward = EPlayerBoostableStat::Health;
		StatRewardAmount = 0;
	}
	
	FQuest(FName QuestName, FName Summary, FName ItemName, int RequiredAmount, EPlayerBoostableStat StatReward, double StatAmount, FName GearReward)
	{
		QuestState = EQuestState::INACTIVE;
		ItemAmountRequired = RequiredAmount;
		QuestDisplayName = QuestName;
		QuestSummary = Summary;
		QuestItem = ItemName;
		this->StatReward = StatReward;
		StatRewardAmount = StatAmount;
		this->GearReward = GearReward;
	}
};
