// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.generated.h"


UENUM(BlueprintType)
enum class EStates : uint8
{
	State1	UMETA(DisplayName = "State1"),
	State2  UMETA(DisplayName = "State2"),
};

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();
	FVector Location;

	EStates State;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//UPROPERTY(EditAnywhere)
	//FVector Location;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
