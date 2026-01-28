// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleInteractive.h"
#include "GameFramework/Actor.h"
#include "PushableEntity.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APushableEntity : public APuzzleInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushableEntity();
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APawn* Pawn) override;
	
	bool BeingPushed = false;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APawn* PushingPawn;
	
// protected:
// 	virtual void BeginPlay() override;
//
// public:
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
};
