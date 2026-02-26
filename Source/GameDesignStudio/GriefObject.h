// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "GriefObject.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API AGriefObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGriefObject();
	
	void DisableParticlesInBlueprint();
	void EnableParticlesInBlueprint();
	
	UPROPERTY(EditAnywhere, Category = "Blueprint Class")
		AActor* BlueprintActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
