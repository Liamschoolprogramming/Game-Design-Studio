#include "PuzzleInteractive_Pickupable.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/PuzzleInventoryManager.h"

APuzzleInteractive_Pickupable::APuzzleInteractive_Pickupable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APuzzleInteractive_Pickupable::Tick(float DeltaTime)
{
	if (!bPushable && bBeingCarried && CarryingCharacter != nullptr)
	{
		//this->SetActorLocation(CarryingCharacter->GetActorLocation() + CarryingCharacter->GetActorForwardVector() * 200);
		
	}
	
}

void APuzzleInteractive_Pickupable::ResetCollision()
{
	SetActorEnableCollision(true);
}

void APuzzleInteractive_Pickupable::Interact(APlayerCharacter* PlayerCharacter)
{
	if (bBeingCarried)
	{
		Drop();
		
	}
	else
	{
		if (IsInRange(PlayerCharacter) && CanPickup())
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
				PlayerCharacter->PickupableObject = this;
				bBeingCarried = true;
				SetActorEnableCollision(false);
				
				AttachPickupAble(true);
				
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, FName("ResetCollision"));
				GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
			}
		}
	}
}

void APuzzleInteractive_Pickupable::PutAway()
{
	if (bBeingCarried)
	{
		int index = GetInventorySlotIndex();
		UPuzzleInventoryManager* PuzzleInventoryManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPuzzleInventoryManager();
		PuzzleInventoryManager->RemovePuzzleSlotElementFromLevel(index);
		Destroy();
	}
}

void APuzzleInteractive_Pickupable::Drop()
{
	bBeingCarried = false;
	CarryingCharacter = nullptr;
	SetActorEnableCollision(true);
	AttachPickupAble(false);
}

void APuzzleInteractive_Pickupable::AttachPickupAble_Implementation(bool Attach)
{
	
}

bool APuzzleInteractive_Pickupable::CanPickup()
{
	FHitResult HitResult;
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector Start = PlayerCharacter->GetActorLocation();
	Start.Z = Start.Z + 50;
	FVector End = GetActorLocation() + (PlayerCharacter->GetActorForwardVector() * 5000.f);
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);      
	Params.AddIgnoredActor(PlayerCharacter);
	Params.bTraceComplex = true;          

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera,Params );
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor != nullptr && HitActor->ActorHasTag("PickupBlocker"))
		{
			return false;
		}
	}
	
	// otherwise
	return true;
}

void APuzzleInteractive_Pickupable::RotatePrism_Implementation(FVector2D InputValue) { }

void APuzzleInteractive_Pickupable::SetRotationMode(bool RotationModeActive)
{
	isRotating = RotationModeActive;
}