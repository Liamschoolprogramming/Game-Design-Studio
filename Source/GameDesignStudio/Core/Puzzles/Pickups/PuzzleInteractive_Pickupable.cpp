#include "PuzzleInteractive_Pickupable.h"
#include "Kismet/KismetMathLibrary.h"

APuzzleInteractive_Pickupable::APuzzleInteractive_Pickupable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APuzzleInteractive_Pickupable::Tick(float DeltaTime)
{
	if (!bPushable && bBeingCarried && CarryingCharacter != nullptr)
	{
		this->SetActorLocation(CarryingCharacter->GetActorLocation() + CarryingCharacter->GetActorForwardVector() * 200);
	}
}

void APuzzleInteractive_Pickupable::Interact(APlayerCharacter* PlayerCharacter)
{
	if (bBeingCarried)
	{
		bBeingCarried = false;
		CarryingCharacter = nullptr;
	}
	else
	{
		if (IsInRange(PlayerCharacter))
		{
			bool bPickupable = false;
			for (int i = 0; i < InteractableCharacterTypes.Num(); i++)
			{
				if (InteractableCharacterTypes[i] == PlayerCharacter-> PlayerCharacterType)
				{
					bPickupable = true;
				}
			}
			if (bPickupable)
			{
				CarryingCharacter = PlayerCharacter;
				bBeingCarried = true;
			}
		}
	}
}

void APuzzleInteractive_Pickupable::Drop()
{
	bBeingCarried = false;
	CarryingCharacter = nullptr;
}