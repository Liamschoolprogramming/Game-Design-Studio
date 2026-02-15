#pragma once

#include "CoreMinimal.h"
#include "PersistantPuzzleState.generated.h"

USTRUCT(BlueprintType)
struct FPersistantPuzzleState
{
	
	GENERATED_BODY()
	
	UPROPERTY()
	TSet<FName> CompletedStates;
	
	FPersistantPuzzleState() { };
	
};
