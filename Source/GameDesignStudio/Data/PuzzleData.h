#pragma once

#include "CoreMinimal.h"
#include "PersistantActorValues.h"
#include "PuzzleData.generated.h"


USTRUCT()
struct FPuzzleData
{
	GENERATED_BODY()
public:
	
	UPROPERTY(SaveGame)
	FPersistantActorValues ActorValues;
};