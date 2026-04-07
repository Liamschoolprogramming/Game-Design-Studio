// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Puzzles/Pickups/PuzzleInteractive_Pickupable.h"
#include "PrismPedestal.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APrismPedestal : public APuzzleInteractive_Pickupable
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isRotating = false;
	
	UFUNCTION(BlueprintNativeEvent)
	void RotatePrism(FVector2D InputValue);
	
	void SetRotationMode(bool RotationModeActive);
};
