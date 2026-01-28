
#include "PushableEntity.h"


APushableEntity::APushableEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APushableEntity::Interact(APawn* Pawn)
{
	// check if pawn can push
	// if so, lock movement of pawn
	// snap position to follow pawn
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacting!"));
	}
}

