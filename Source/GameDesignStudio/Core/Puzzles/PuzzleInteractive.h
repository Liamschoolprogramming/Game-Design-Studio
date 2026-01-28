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
	virtual bool Interact(APawn* Pawn);
	
	UPROPERTY(BlueprintReadWrite)
	double InteractRange = 10;
protected:
	virtual bool IsInRange(APawn* Pawn);
};
