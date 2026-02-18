#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "data/PersistentActorId.h"
#include "Core/Debug/DebugUtils.h"
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
	
	TMap<FName, TWeakObjectPtr<APuzzle>>& GetRuntimeActors();
	
	// A helper method to search through the list of actors in the WorldSubsystem
	// and return a map of them that is a local variable
	
	// for (declaration : range)
	// declaration->action()
	
	// Make blueprintable
	TArray<APuzzle*> GetActorsOfManagerType(TSubclassOf<UGameManagerBase> Manager);

private:
	
	// Key will be the unique actor key
	TMap<FName, TWeakObjectPtr<APuzzle>> RuntimeActors;
	
};