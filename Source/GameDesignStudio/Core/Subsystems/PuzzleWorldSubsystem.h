#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "data/PersistentActorId.h"

#include "core/Puzzles/Puzzle.h"
#include "PuzzleWorldSubsystem.generated.h"

// Maybe rename to something broad since I think this will be spawned each level
// then have the level managers be unique

class APuzzle;

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UPuzzleWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	virtual void PostInitialize();
	
	// Actor needs to call this method
	void RegisterPuzzleActor(APuzzle* Actor);

private:
	
	// Key will be the unique actor key
	TMap<FName, TWeakObjectPtr<APuzzle>> RuntimeActors;
	
};