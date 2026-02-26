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

// Equips the provided gear in its designated slot. Returns the gear being replaced.
FPlayerInventoryItem UGearManager::EquipGear(FPlayerInventoryItem Gear)
{
	FPlayerInventoryItem ReplacedGear;
	
	switch (Gear.GearInfo.GearType)
	{
		case EGearType::Head:
			ReplacedGear = *PlayerGear.Find("Head");
			PlayerGear.Add("Head", Gear);
			break;
		case EGearType::Body:
			ReplacedGear = *PlayerGear.Find("Body");
			PlayerGear.Add("Body", Gear);
			break;
		case EGearType::Legs:
			ReplacedGear = *PlayerGear.Find("Legs");
			PlayerGear.Add("Legs", Gear);
			break;
	}
	
	RemoveGearStats(ReplacedGear);
	ApplyGearStats(Gear);
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

