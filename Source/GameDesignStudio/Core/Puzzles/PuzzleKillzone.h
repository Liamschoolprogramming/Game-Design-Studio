// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Managers/PlayerStatManager.h"
#include "PuzzleKillzone.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleKillzone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleKillzone();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	bool KillAnyPlayer = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	EPlayerCharacterType PlayerToKill = EPlayerCharacterType::Default;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	FVector BoxSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hitbox")
	UBoxComponent* KillComponent;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, 
								AActor* OtherActor, 
								UPrimitiveComponent* OtherComp, 
								int32 OtherBodyIndex, 
								bool bFromSweep, 
								const FHitResult& SweepResult);
};
