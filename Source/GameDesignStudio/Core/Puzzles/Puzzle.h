// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/PersistantActorValues.h"
#include "Core/Managers/GameManagerBase.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPuzzleState PuzzleStatus = EPuzzleState::Start;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameManagerBase> OwningManager;
	
	// Weak pointers don't prevent another actor from being destroyed
	TWeakObjectPtr<AActor> WorldSubsytem;
	FPersistantActorValues ActorValues;
	
	//UPROPERTY(EditAnywhere)
	//FName StateId;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzle Actors")
	void SetState(EPuzzleState State);
	
	// Set as blueprint overrideable
	//virtual void DoActionBasedOnState(EPuzzleStatus State);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//void InitializeState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
