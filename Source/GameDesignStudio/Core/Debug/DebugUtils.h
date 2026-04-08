#pragma once
#include "CoreMinimal.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#if !UE_BUILD_SHIPPING
#define DEBUG_TO_SCREEN(Color, Format, ...) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__)); }

#else
#define DEBUG_TO_SCREEN(Color, Format, ...)
#endif


namespace DebugUtils
{
	static void LogToFile(const UObject* Caller, const FString& Message)
	{
		FString CallerInfo = Caller ? FString::Printf(TEXT("[%s] "), *Caller->GetName()) : TEXT("[Unknown] ");
		FString PathToSave = FPaths::ProjectSavedDir() / TEXT("PuzzleDebug.log");
		FString Line = FDateTime::Now().ToString() + TEXT(" ") + CallerInfo + Message + LINE_TERMINATOR;
		FFileHelper::SaveStringToFile(Line, *PathToSave, FFileHelper::EEncodingOptions::AutoDetect,
			&IFileManager::Get(), FILEWRITE_Append);
	}
}

// Copied from Puzzle.cpp SetState method

//***************************************************//
// For debug display naming of states
// const UEnum* Enum = StaticEnum<EPuzzleState>();
	
// FName StateName = Enum->GetNameByValue(static_cast<int64>(State));
// StateName = FName(*Enum->GetNameStringByValue(static_cast<int64>(PuzzleStatus)));
//****************************************************//