#pragma once

#include "CoreMinimal.h"
#include "PuzzleIds.h"
#include "PersistentActorId.generated.h"


USTRUCT()
struct FPersistentActorId
{
	
	GENERATED_BODY()
	
	// Ideally we'd have this puzzleId struct with the
	// location and puzzle coupled together. A specific
	// PuzzleId should be fine for now though for early
	// testing
	
	//UPROPERTY()
	//FPuzzleIds PuzzleId;
	
	// Actors passes in a struct of its states and it's unqiue ID
	// FPuzzleIds contains the puzzleid and it's state
	
	// Then the key of the actors unique id is used to access this
	// Actor should update this data type when it changes state so
	// the manager can have a record of this change so this probably
	// does need to be implemented this way
	
	// Manager needs a hash to a data structure that holds the data
	// of the object. The hash could be the name of the actor and the
	// data structure be the struct and fields of info
	
	UPROPERTY()
	FName PuzzleId;
	
	UPROPERTY()
	FName ActorId;

};
