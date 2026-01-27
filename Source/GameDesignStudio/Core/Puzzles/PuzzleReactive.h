// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleReactive.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleReactive : public APuzzle
{
	GENERATED_BODY()
	
public:
	//Constructor declaration
	APuzzleReactive();
		
protected:
	//Defines static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")	
	UStaticMeshComponent* BaseMesh;
	
	//Creates Activated bool (ex: tells a door to start opening or closing)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bActivated;
	
	//Creates CompletedReaction bool (ex: is true when a door is fully opened or closed)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCompletedReaction;
	
public:
	//Defines function for the puzzle object to react
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActivatePuzzle();
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	//Defines function foe the puzzle to stop reacting
	void DeactivatePuzzle();
};
