// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDeviceNull.h"
//#include "Managers/PuzzleGriefManager.h"
#include "GameFramework/Actor.h"
#include "GriefObject.generated.h"

class UPuzzleGriefManager;

UCLASS()
class GAMEDESIGNSTUDIO_API AGriefObject : public AActor
{
	GENERATED_BODY()
	
	UPuzzleGriefManager* GriefManager;
public:	
	// Sets default values for this actor's properties
	AGriefObject();
	
	void DisableParticlesInBlueprint();
	void EnableParticlesInBlueprint();
	
	UPROPERTY(EditAnywhere, Category = "Blueprint Class")
		AActor* BlueprintActor;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Manager")
		TSubclassOf<UPuzzleGriefManager> OwningManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
