// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Core/Puzzles/Puzzle.h"
#include "PuzzleGoal.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleGoal : public APuzzle
{
	GENERATED_BODY()
	
public:
	APuzzleGoal();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void OnOverlap( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
};
