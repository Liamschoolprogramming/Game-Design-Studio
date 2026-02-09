#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "InventoryManager.generated.h"

UENUM(Blueprintable)
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

UCLASS()
class GAMEDESIGNSTUDIO_API UInventoryManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FPlayerInventoryItem> PlayerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FPlayerInventoryItem> AllItems;
	
	UFUNCTION(BlueprintCallable)
	int AddToInventory(FName ItemName, int Amount);
	
	UFUNCTION(BlueprintCallable)
	int RemoveFromInventory(FName ItemName, int Amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxAmountForItem(FName ItemName, int MaxAmount);
	
	UFUNCTION(BlueprintCallable)
	FPlayerInventoryItem GetItemDetails(FName ItemName);

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmountForItem(FName ItemName);
};