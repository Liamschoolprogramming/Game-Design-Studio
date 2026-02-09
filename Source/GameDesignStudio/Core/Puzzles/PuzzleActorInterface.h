#pragma once

#include "PuzzleActorInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPuzzleActorInterface : public UInterface
{
	GENERATED_BODY()
	
};

class IPuzzleActorInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyPuzzleState();
	
};
