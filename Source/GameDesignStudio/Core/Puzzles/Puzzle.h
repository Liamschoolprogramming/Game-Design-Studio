// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/PersistantActorValues.h"
#include "Core/Managers/GameManagerBase.h"
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

/*
UENUM(Blueprintable)
enum class EPuzzleActorSignalState : uint8 {
	Active UMETA(DisplayName = "Green"),
	Red UMETA(DisplayName = "Red"),
};*/

UCLASS(Abstract)
class GAMEDESIGNSTUDIO_API APuzzle : public AActor
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Managers", meta = (DeterminesOutputType = "ManagerClass"))
	UGameManagerBase* GetOwningManagerClass(TSubclassOf<UGameManagerBase> ManagerClass);
	

	
public:	
	APuzzle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FName ActorId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	EPuzzleActorType PuzzleActorType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameManagerBase> OwningManager;
	
	// Weak pointers don't prevent another actor from being destroyed
	TWeakObjectPtr<AActor> WorldSubsytem;
	FPersistantActorValues ActorValues;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	APuzzle* LinkedReceiver;
	
	//void SetActorID(FName Id) const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
