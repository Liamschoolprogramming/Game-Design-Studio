
#include "PuzzleInteractive_StatBooster.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/PlayerStatManager.h"

APuzzleInteractive_StatBooster::APuzzleInteractive_StatBooster()
{
}

void APuzzleInteractive_StatBooster::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzleInteractive_StatBooster::PickupStatBoost()
{
	if (!bPickedUp)
	{
		bPickedUp = true;
		UPlayerStatManager* PlayerStatManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager();
		PlayerStatManager->BoostPlayerStat(StatToBoost, BoostAmount);
		Destroy();
	}
}