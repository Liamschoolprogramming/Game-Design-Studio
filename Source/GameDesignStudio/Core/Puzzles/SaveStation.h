// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Puzzles/PuzzleInteractive.h"
#include "SaveStation.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API ASaveStation : public APuzzleInteractive
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (InstanceEditable = "true", MakeEditWidget))
	FVector SpawnLocation;
};
