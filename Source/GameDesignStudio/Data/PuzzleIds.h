#pragma once

#include "CoreMinimal.h"
#include "PuzzleIds.generated.h"
	

// Define struct values here, use struct as a variable in
// managers and set the struct values

// For example struct will be of PuzzleId and StepId, the struct will be referenced as 
// a variable in each manager and then those values can be referenced by anyone that needs
// to access it

// For example FPuzzleIds PuzzleRiverManagerIds
USTRUCT(BlueprintType)
struct FPuzzleIds
{
	GENERATED_BODY()
	
	// Location of puzzle
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Area;
	
	// Specific puzzle
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Puzzle;
	
	
};

// Combine two hash values
//FORCEINLINE GetTypeHash(const FPuzzleIds& Id)
//{
	//return HashCombine(Id.PuzzleId, Id.StepId);	
//}
