#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleInteractive.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive : public APuzzle
{
	GENERATED_BODY()
	
public:
	virtual void Interact(APawn* Pawn);
};
