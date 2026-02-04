#pragma once

#include "CoreMinimal.h"
#include "PersistantActorValues.generated.h"


USTRUCT()
struct FPersistantActorValues
{
	GENERATED_BODY()
	
	UPROPERTY()
	FTransform ActorLocation;
	
	UPROPERTY()
	TSet<FName> VisualStates;
	
	UPROPERTY()
	FName StateId;
};
