// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleValidationSubsystem.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Engine/world.h"
#include "EngineUtils.h"
#include "core/Puzzles/Puzzle.h"
#include "core/Managers/GameManagerBase.h"


void UPuzzleValidationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
#if WITH_EDITOR
	FEditorDelegates::PreBeginPIE.AddUObject(this, &UPuzzleValidationSubsystem::PrePIECheck);
#endif
}


void UPuzzleValidationSubsystem::Deinitialize()
{
	#if WITH_EDITOR
		FEditorDelegates::PreBeginPIE.RemoveAll(this);
	#endif
}


void UPuzzleValidationSubsystem::PrePIECheck(bool bScanning)
{
	
}


