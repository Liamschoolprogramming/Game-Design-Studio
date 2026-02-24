#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "PlayerStatManager.h"
#include "InventoryManager.generated.h"

UENUM(Blueprintable)
enum class EInventoryItemType : uint8
{
	Quest UMETA(DisplayName = "Quest"),
	Gear UMETA(DisplayName = "Gear"),
};

UENUM(Blueprintable)
enum class EGearType : uint8
{
	Head UMETA(DisplayName = "Head"),
	Body UMETA(DisplayName = "Body"),
	Legs UMETA(DisplayName = "Legs"),
};

USTRUCT(BlueprintType)
struct FGearInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, double> StatBoosts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> AbilityTags;
	
	EGearType GearType;
	
	FGearInfo()
	{
		StatBoosts = TMap<FName, double>();
		AbilityTags = TArray<FName>();
		GearType = EGearType::Body;
	}
	
	FGearInfo(TMap<FName, double> StatBoosts, TArray<FName> AbilityTags, EGearType GearType)
	{
		this->StatBoosts = StatBoosts;
		this->AbilityTags = AbilityTags;
		this->GearType = GearType;
	}
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hidden;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGearInfo GearInfo;
	
	FPlayerInventoryItem()
	{
		MaxAmount = 1000;
		CurrentAmount = 0;
		ItemType = EInventoryItemType::Quest;
		Hidden = false;
	}
	
	//Simple Constructor, No Gear Info & Not Hidden
	FPlayerInventoryItem(FName ItemName, int Amount, int Max, EInventoryItemType InvItemType)
	{
		CurrentAmount = Amount;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
		ItemType = InvItemType;
		Hidden = false;
		GearInfo = FGearInfo();
	}
	
	//Constructor with Hidden value, used for Quests without an actual item (Ex: Golem Quest)
	FPlayerInventoryItem(FName ItemName, int Amount, int Max, EInventoryItemType InvItemType, bool InvHidden)
	{
		CurrentAmount = Amount;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
		ItemType = InvItemType;
		Hidden = InvHidden;
		GearInfo = FGearInfo();
	}
	
	//Constructor with Gear Info, should be used when making gear
	FPlayerInventoryItem(FName ItemName, int Amount, int Max, FGearInfo GearStats)
	{
		CurrentAmount = Amount;
		MaxAmount = Max;
		ItemDisplayName = ItemName;
		ItemType = EInventoryItemType::Gear;
		Hidden = false;
		GearInfo = GearStats;
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