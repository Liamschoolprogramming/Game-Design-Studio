// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/PersistantActorValues.h"
#include "Puzzle.generated.h"

UCLASS(Abstract)
class GAMEDESIGNSTUDIO_API APuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FName ActorId;
	
	// Weak pointers don't prevent another actor from being destroyed
	TWeakObjectPtr<AActor> WorldSubsytem;
	FPersistantActorValues ActorValues;
	
	//void SetActorID(FName Id) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
