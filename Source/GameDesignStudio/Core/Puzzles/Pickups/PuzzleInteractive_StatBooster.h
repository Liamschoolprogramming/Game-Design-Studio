// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleInteractive_StatBooster.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive_StatBooster : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	EPlayerBoostableStat StatToBoost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	double BoostAmount;
	
	UFUNCTION(BlueprintCallable)
	void PickupStatBoost();
	
	APuzzleInteractive_StatBooster();

protected:
	virtual void BeginPlay() override;
	
	bool bPickedUp = false;
};
