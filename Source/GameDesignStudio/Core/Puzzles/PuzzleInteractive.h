#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
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
	virtual void Interact(APlayerCharacter* PlayerCharacter);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double InteractRange = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (
		InstanceEditable = "true", ExposeOnSpawn = "true"))
	TArray<EPlayerCharacterType> InteractableCharacterTypes;
	
protected:
	virtual bool IsInRange(APlayerCharacter* PlayerCharacter);
};
