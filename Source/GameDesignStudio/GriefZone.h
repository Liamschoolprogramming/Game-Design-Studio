// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Core/Puzzles/Puzzle.h"
#include "GriefZone.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API AGriefZone : public APuzzle
{
	GENERATED_BODY()
	
	
public:
	AGriefZone();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* GriefEffect;
};
