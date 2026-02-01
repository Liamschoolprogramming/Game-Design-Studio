#pragma once

#include "CoreMinimal.h"
#include "PersistentActorId.h"


USTRUCT()
struct FPersistantActorValues
{
	GENERATED_BODY()
	
	UPROPERTY()
	FTransform ActorLocation;
	
	UPROPERTY()
	TSet<FName> VisualStates;
	
	
};
