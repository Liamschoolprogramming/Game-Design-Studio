// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatManager.h"

void UPlayerStatManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	PlayerStats = FPlayerStats();
}

FPlayerStats UPlayerStatManager::GetPlayerStats()
{
	return PlayerStats;
}

void UPlayerStatManager::BoostPlayerStat(EPlayerBoostableStat StatToBoost, double Amount)
{
	switch (StatToBoost)
	{
		case EPlayerBoostableStat::Health:
			PlayerStats.HealthPoints += Amount;
			break;
		case EPlayerBoostableStat::Stamina:
			PlayerStats.StaminaPoints += Amount;
			break;
		case EPlayerBoostableStat::Mind:
			PlayerStats.MindPoints += Amount;
			break;
	}
}