// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "PuzzleValidationSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UPuzzleValidationSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	
	
	
private:
	
	void PrePIECheck(bool bScanning);
	
	bool ValidatePuzzleActors(UWorld* World);
	
};
