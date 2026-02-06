// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatManager.h"

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
		case EPlayerBoostableStat::Stamina:
			PlayerStats.StaminaPoints += Amount;
		case EPlayerBoostableStat::Mind:
			PlayerStats.MindPoints += Amount;
		default:
	}
}