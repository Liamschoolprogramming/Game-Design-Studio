// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/PersistantActorValues.h"
#include "Core/Managers/GameManagerBase.h"
#include "PuzzleActorInterface.h"
#include "Puzzle.generated.h"

UENUM(Blueprintable)
enum class EPuzzleActorType : uint8
{
	// Also called Triggers, e.g. Pressure Plants and PhotonPowerTriggers. Send red/green signals to Receivers.
	SignalEmitter UMETA(DisplayName = "SignalEmitter"),
	// Vine Doors and Turrets. Red/green signals change their behavior.
	SignalReceiver UMETA(DisplayName = "SignalReceiver"),
	// Light Sources and Movable Light Sources. 
	PowerSource UMETA(DisplayName = "PowerSource"),
	// Channels and Preservers/Inverters
	Redirector UMETA(DisplayName = "Redirector"),
	// Boulders, etc.
	Basic UMETA(DisplayName = "Basic"),
};

UENUM(Blueprintable)
enum class EPuzzleElementState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Preserved UMETA(DisplayName = "Preserved"),
	Inverted UMETA(DisplayName = "Inverted"),
};

UCLASS(Abstract)
class GAMEDESIGNSTUDIO_API APuzzle : public AActor, public IPuzzleActorInterface
{
	GENERATED_BODY()
	
public:	
	APuzzle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FName ActorId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPuzzleState PuzzleStatus = EPuzzleState::Start;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	EPuzzleActorType PuzzleActorType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameManagerBase> OwningManager;
	
	// Weak pointers don't prevent another actor from being destroyed
	TWeakObjectPtr<AActor> WorldSubsytem;
	FPersistantActorValues ActorValues;
	
	//UPROPERTY(EditAnywhere)
	//FName StateId;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzle Actors")
	void SetState(EPuzzleState State);
	
	
	virtual void ApplyPuzzleState_Implementation();
	
	// Set as blueprint overrideable
	//virtual void DoActionBasedOnState(EPuzzleStatus State);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, bool> Signals;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	APuzzle* LinkedReceiver;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	EPuzzleElementState PuzzleElementState;
	
	//void SetActorID(FName Id) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//void InitializeState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};