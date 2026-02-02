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

UENUM(Blueprintable)
enum class EPlayerCharacterType : uint8
{
	Default UMETA(DisplayName = "Default"),
	Golem UMETA(DisplayName = "Golem"),
};

UENUM()
enum class EInventoryItemType : uint8
{
	Quest UMETA(DisplayName = "Quest"),
	Gear UMETA(DisplayName = "Gear"),
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInventoryItemType ItemType;
	
	FPlayerInventoryItem()
	{
		MaxAmount = 1000;
		CurrentAmount = 0;
		ItemType = EInventoryItemType::Quest;
	}
	
	FPlayerInventoryItem(FName ItemName, int Amount, int Max, EInventoryItemType InvItemType)
	{
		CurrentAmount = Amount;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
		ItemType = InvItemType;
	}
};