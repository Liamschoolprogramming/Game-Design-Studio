// Fill out your copyright notice in the Description page of Project Settings.

#include "GearManager.h"

#include "InventoryInterface.h"
#include "Managers/InventoryManager.h"
#include "Managers/PlayerStatManager.h"
#include "Blueprint/UserWidget.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

const FPlayerInventoryItem EmptyGear = FPlayerInventoryItem("None",TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Game/GameDesignStudio/Art/UI/T_Placeholder.T_Placeholder"))),"Nothing.",0, 0, FGearInfo());

void UGearManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerGear = {
		{"Head", EmptyGear},
		{"Body", EmptyGear},
		{"Legs", EmptyGear},
	};
}

/**
 * Unequips gear of the provided type
 * @param GearType
 * @return The gear that was unequipped
 */
FPlayerInventoryItem UGearManager::UnequipGear(EGearType GearType)
{
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	
	FPlayerInventoryItem UnequippedGear;
	
	switch (GearType)
	{
	case EGearType::Head:
		UnequippedGear = PlayerGear.FindRef("Head");
		PlayerGear.Add("Head", EmptyGear);
		break;
	case EGearType::Body:
		UnequippedGear = PlayerGear.FindRef("Body");
		PlayerGear.Add("Body", EmptyGear);
		break;
	case EGearType::Legs:
		UnequippedGear = PlayerGear.FindRef("Legs");
		PlayerGear.Add("Legs", EmptyGear);
		break;
	}
	
	RemoveGearStats(UnequippedGear);
	
	IInventoryInterface::Execute_OnGearChanged(InventoryManager->InventoryMenu, GearType, UnequippedGear.ItemDisplayName, "None");
	
	if (UnequippedGear.ItemDisplayName != "None")
	{
		InventoryManager->AddToInventory(UnequippedGear.ItemDisplayName, 1);
	}
	return UnequippedGear;
}

/**
 * Equips the provided gear in its designated slot.
 * @param Gear
 * @return The gear that was replaced
 */
FPlayerInventoryItem UGearManager::EquipGear(FPlayerInventoryItem Gear)
{
	UInventoryManager* InventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetInventoryManager();
	
	FPlayerInventoryItem ReplacedGear;
	
	switch (Gear.GearInfo.GearType)
	{
		case EGearType::Head:
			ReplacedGear = UnequipGear(EGearType::Head);
			PlayerGear.Add("Head", Gear);
			break;
		case EGearType::Body:
			ReplacedGear = UnequipGear(EGearType::Body);
			PlayerGear.Add("Body", Gear);
			break;
		case EGearType::Legs:
			ReplacedGear = UnequipGear(EGearType::Legs);
			PlayerGear.Add("Legs", Gear);
			break;
	}
	
	InventoryManager->RemoveFromInventory(Gear.ItemDisplayName, 1);
	ApplyGearStats(Gear);
	
	IInventoryInterface::Execute_OnGearChanged(InventoryManager->InventoryMenu, Gear.GearInfo.GearType, ReplacedGear.ItemDisplayName, Gear.ItemDisplayName);
	
	return ReplacedGear;
}

/**
 * Applies stats from the provided gear piece and any ability tags.
 * @param Gear
 */
void UGearManager::ApplyGearStats(FPlayerInventoryItem Gear)
{
	UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
	
	double HealthBoost = Gear.GearInfo.StatBoosts.FindRef("Health");
	double StaminaBoost = Gear.GearInfo.StatBoosts.FindRef("Stamina");
	double MindBoost = Gear.GearInfo.StatBoosts.FindRef("Mind");
	
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Health, HealthBoost);
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Stamina, StaminaBoost);
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Mind, MindBoost);
}

/**
 * Removes stats from the provided gear piece and any ability tags.
 * @param Gear
 */
void UGearManager::RemoveGearStats(FPlayerInventoryItem Gear)
{
	UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
	
	double HealthBoost = Gear.GearInfo.StatBoosts.FindRef("Health");
	double StaminaBoost = Gear.GearInfo.StatBoosts.FindRef("Stamina");
	double MindBoost = Gear.GearInfo.StatBoosts.FindRef("Mind");
	
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Health, -HealthBoost);
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Stamina, -StaminaBoost);
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Mind, -MindBoost);
}

