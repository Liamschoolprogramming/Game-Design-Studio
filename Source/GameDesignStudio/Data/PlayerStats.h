#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	double PossessRange;
		
	UPROPERTY(EditAnywhere)
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
	
	UPROPERTY(EditAnywhere)
	FName ItemDisplayName;
	
	UPROPERTY(EditAnywhere)
	int CurrentAmount;
	
	UPROPERTY(EditAnywhere)
	int MaxAmount;
	
	FPlayerInventoryItem()
	{
		MaxAmount = 1000;
		CurrentAmount = 0;
	}
	
	FPlayerInventoryItem(FName ItemName, int Max)
	{
		CurrentAmount = 0;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
	}
};