// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnablePostProcess.generated.h"

UCLASS(Abstract, Blueprintable)
class GAMEDESIGNSTUDIO_API ASpawnablePostProcess : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnablePostProcess();
	
	
	
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Post Process")
	TObjectPtr<UPostProcessComponent> PostProcessComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Post Process")
	/**
	 * If > 0, the subsystem will auto-remove this after this many seconds.
	 * Set to 0 for indefinite lifetime (manual remove required).
	 */
	float LifetimeDuration = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Post Process")
	int32 Priority = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Post Process")
	void OnPostProcessActivated();

	
	UFUNCTION(BlueprintImplementableEvent, Category = "Post Process")
	void OnPostProcessDeactivated();

	friend class UPostProcessSubsystem;

};
