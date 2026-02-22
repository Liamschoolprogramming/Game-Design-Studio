#pragma once
#include "CoreMinimal.h"

#if !UE_BUILD_SHIPPING
#define DEBUG_TO_SCREEN(Color, Format, ...) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }

#else
#define DEBUG_TO_SCREEN(Color, Format, ...)
#endif

// Copied from Puzzle.cpp SetState method

//***************************************************//
// For debug display naming of states
// const UEnum* Enum = StaticEnum<EPuzzleState>();
	
// FName StateName = Enum->GetNameByValue(static_cast<int64>(State));
// StateName = FName(*Enum->GetNameStringByValue(static_cast<int64>(PuzzleStatus)));
//****************************************************//