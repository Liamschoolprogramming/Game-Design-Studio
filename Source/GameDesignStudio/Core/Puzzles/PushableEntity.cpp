
#include "PushableEntity.h"

#include "EditorCategoryUtils.h"


APushableEntity::APushableEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractRange = 100;
	
}

void APushableEntity::Tick(float DeltaTime)
{
	if (BeingPushed && PushingPawn != nullptr)
	{
		//this->SetActorLocation(PushingPawn->GetActorLocation());
	}
}

void APushableEntity::Interact(APawn* Pawn)
{
	// check if pawn can push
	// if so, lock movement of pawn
	// snap position to follow pawn
	if (BeingPushed)
	{
		BeingPushed = false;
		PushingPawn = nullptr;
	}
	else
	{
		if (IsInRange(Pawn))
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacting!"));
			}
			PushingPawn = Pawn;
		}
	}
}