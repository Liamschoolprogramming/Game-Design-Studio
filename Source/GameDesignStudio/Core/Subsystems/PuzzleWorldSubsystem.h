#pragma once

#include "CoreMinimal.h"
#include "Core/ELSSaveGame.h"
#include "Subsystems/WorldSubsystem.h"
#include "data/PersistentActorId.h"
#include "Core/Debug/DebugUtils.h"
#include "core/Puzzles/Puzzle.h"
#include "Core/Puzzles/PuzzleOwner.h"
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
	
	UFUNCTION(BlueprintCallable)
	void RegisterPuzzleOwner(APuzzleOwner* InPuzzleOwner);
	
	UPROPERTY()
	TArray<APuzzleOwner*> PuzzleOwners;
	
	TArray<FPuzzleOwnerData> CaptureAllStates();
	
	void RestoreAllStates(const TArray<FPuzzleOwnerData>& AllStates);
	
private:
	
	
};