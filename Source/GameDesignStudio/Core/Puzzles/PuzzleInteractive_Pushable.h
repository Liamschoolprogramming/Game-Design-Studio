// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleInteractive.h"
#include "GameFramework/Actor.h"
#include "PuzzleInteractive_Pushable.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive_Pushable : public APuzzleInteractive
{
	GENERATED_BODY()

public:
	APuzzleInteractive_Pushable();
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APawn* Pawn) override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APawn* PushingPawn;
	
protected:
	bool BeingPushed = false;
	FVector Offset = FVector(100,100,0);
	
};
