#include "PuzzleInteractive_Pickupable.h"
#include "EditorCategoryUtils.h"
#include "VectorTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

APuzzleInteractive_Pickupable::APuzzleInteractive_Pickupable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APuzzleInteractive_Pickupable::Tick(float DeltaTime)
{
	if (bIsPushable)
	{
		if (bBeingCarried && CarryingCharacter != nullptr)
		{
			
		}
		return;
	}
	
	if (bBeingCarried && CarryingCharacter != nullptr)
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
			
			if (bIsPushable)
			{
				FVector ForwardDirection = CarryingCharacter->GetActorForwardVector();
				FVector NormalizedPushDirection (
					UKismetMathLibrary::Round(ForwardDirection.X), 
					UKismetMathLibrary::Round(ForwardDirection.Y), 
					UKismetMathLibrary::Round(ForwardDirection.Z));
		
				CarryingCharacter->GetCharacterMovement()->DisableMovement();
				CarryingCharacter->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				PushDirection = NormalizedPushDirection;
			}
		}
	}
}

void APuzzleInteractive_Pickupable::Drop()
{
	bBeingCarried = false;
	CarryingCharacter = nullptr;
	if (bIsPushable)
	{
		CarryingCharacter->GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	}
}