#pragma once
#include "CoreMinimal.h"
#include "PuzzleOwnerData.h"
#include "PuzzleWorldData.generated.h"

USTRUCT()
struct FPuzzleWorldData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(SaveGame)
	TArray<FPuzzleOwnerData> PuzzleOwners;
};
