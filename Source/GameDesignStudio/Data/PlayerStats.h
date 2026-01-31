#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PossessRange;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double InteractRange;
	
	FPlayerStats()
	{
		PossessRange = 500.0;
		InteractRange = 500.0;
	}
};

UENUM()
enum class EPlayerCharacterType : uint8
{
	Default UMETA(DisplayName = "Default"),
	Golem UMETA(DisplayName = "Golem"),
};

USTRUCT(BlueprintType)
struct FPlayerInventoryItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmount;
	
	FPlayerInventoryItem()
	{
		MaxAmount = 1000;
		CurrentAmount = 0;
	}
	
	FPlayerInventoryItem(FName ItemName, int Amount, int Max)
	{
		CurrentAmount = Amount;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
	}
};