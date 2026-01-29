#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "core/Puzzles/Puzzle.h"
#include "PuzzleStartingWorldSubsystem.generated.h"

// Maybe rename to something broad since I think this will be spawned each level
// then have the level managers be unique

class APuzzle;

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UStartingWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

/*
public:
	virtual void initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void RegisterPuzzleActor(APuzzle* Actor);
	void UnregisterPuzzleActor(APuzzle* Actor);

	void ApplyState(APuzzle* Actor);

private:
	TMap<FPuzzleId, TWeakObjectPtr<APuzzle>> ActiveActors;  
	
	
*/
};