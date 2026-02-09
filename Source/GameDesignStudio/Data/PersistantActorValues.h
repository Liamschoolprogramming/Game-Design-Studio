#pragma once

#include "CoreMinimal.h"
#include "PersistantActorValues.generated.h"

UENUM(BlueprintType)
enum class EPuzzleState : uint8
{
	Start UMETA(DisplayName = "Start"),
	Inactive UMETA(DisplayName = "Inactive"),
	Active UMETA(DisplayName = "Active"),
	Solved UMETA(DisplayName = "Solved"),
	Failed UMETA(DisplayName = "Failed"),
};

USTRUCT()
struct FPersistantActorValues
{
	GENERATED_BODY()
	
	UPROPERTY()
	FTransform ActorLocation;
	
	//UPROPERTY()
	//FName CurrentState;
	
	UPROPERTY()
	EPuzzleState PuzzleState;
	
	UPROPERTY()
	FName StateId;
	
	FPersistantActorValues() {
		PuzzleState = EPuzzleState::Start;
	}
	
};
