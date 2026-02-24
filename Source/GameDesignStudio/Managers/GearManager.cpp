// Fill out your copyright notice in the Description page of Project Settings.

#include "GearManager.h"

#include "Managers/InventoryManager.h"
#include "Managers/PlayerStatManager.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

void UGearManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerGear = {
		{"Head", FPlayerInventoryItem("None", 0, 0, FGearInfo() )},
		{"Body", FPlayerInventoryItem("None", 0, 0, FGearInfo() )},
		{"Legs", FPlayerInventoryItem("None", 0, 0, FGearInfo() )},
	};
}

// Tries to add an item to the inventory, returns new amount in inventory for that item.
FPlayerInventoryItem UGearManager::EquipGear(FPlayerInventoryItem Gear)
{
	FPlayerInventoryItem ReplacedGear;
	
	if (Gear.GearInfo.GearType == EGearType::Head)
	{
		ReplacedGear = *PlayerGear.Find("Head");
		PlayerGear.Add("Head", Gear);
	}
	else if (Gear.GearInfo.GearType == EGearType::Body)
	{
		ReplacedGear = *PlayerGear.Find("Body");
		PlayerGear.Add("Body", Gear);
	}
	else
	{
		ReplacedGear = *PlayerGear.Find("Legs");
		PlayerGear.Add("Legs", Gear);
	}
	
	return ReplacedGear;
}

void UGearManager::ApplyGearStats(FPlayerInventoryItem Gear)
{
	UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
	
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Health, *Gear.GearInfo.StatBoosts.Find("Health"));
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Stamina, *Gear.GearInfo.StatBoosts.Find("Stamina"));
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Mind, *Gear.GearInfo.StatBoosts.Find("Mind"));
}

void UGearManager::RemoveGearStats(FPlayerInventoryItem Gear)
{
	UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
	
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Health, -*Gear.GearInfo.StatBoosts.Find("Health"));
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Stamina, -*Gear.GearInfo.StatBoosts.Find("Stamina"));
	PlayerStatManager->BoostPlayerStat(EPlayerBoostableStat::Mind, -*Gear.GearInfo.StatBoosts.Find("Mind"));
}

