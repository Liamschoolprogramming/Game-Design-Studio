#pragma once

#include "PuzzleActorInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPuzzleActorInterface : public UInterface
{
	GENERATED_BODY()


public:
	
	
	void ApplyPuzzleState();
	
};
