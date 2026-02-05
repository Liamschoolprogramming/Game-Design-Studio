#pragma once

#include "CoreMinimal.h"
#include "QuestData.generated.h"

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemAmountRequired;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Completed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Active;
	
	FQuest()
	{
		Completed = false;
		Active = false;
		ItemAmountRequired = 0;
	}
	
	FQuest(FName QuestName, FName ItemName, int RequiredAmount)
	{
		Completed = false;
		Active = false;
		ItemAmountRequired = RequiredAmount;
		QuestDisplayName = QuestName;
		QuestItem = ItemName;
	}
};
