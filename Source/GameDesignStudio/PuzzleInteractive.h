// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleInteractive.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive : public APuzzle
{
	GENERATED_BODY()
	
public:
	APuzzleInteractive();
	
protected:
	//Defines BaseMesh static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")	
	UStaticMeshComponent* BaseMesh;
	
	//Defines optional Sphere Collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollision;
	

	
};

