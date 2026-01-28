
#include "PushableEntity.h"


APushableEntity::APushableEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractRange = 300;
}

bool APushableEntity::Interact(APawn* Pawn)
{
	// check if pawn can push
	// if so, lock movement of pawn
	// snap position to follow pawn
	if (IsInRange(Pawn))
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacting!"));
		}
		return true;
	}
	return false;
}