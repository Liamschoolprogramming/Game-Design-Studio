
#include "PuzzleInteractive_StatBooster.h"

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
		switch (StatToBoost)
		{
			case EPlayerBoostableStat::Health:
				
		}
		Destroy();
	}
}