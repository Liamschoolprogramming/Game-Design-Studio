#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	double PossessRange;
		
	UPROPERTY(EditAnywhere)
	double InteractRange;
	
	FPlayerStats()
	{
		PossessRange = 500.0;
		InteractRange = 500.0;
	}
};

