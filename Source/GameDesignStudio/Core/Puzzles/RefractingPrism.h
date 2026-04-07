#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickups/PuzzleInteractive_Pickupable.h"
#include "RefractingPrism.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API ARefractingPrism : public APuzzleInteractive_Pickupable
{
	GENERATED_BODY()
	
public:
	ARefractingPrism();
};
