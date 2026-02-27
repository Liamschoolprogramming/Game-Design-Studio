// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraControlComponent.generated.h"


UCLASS(ClassGroup=(Camera), meta=(BlueprintSpawnableComponent), Blueprintable)
class DIALOGUEASSETEDITORRUNTIME_API UCameraControlComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCameraControlComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Lens")
	float FocalLength = 50.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Focus")
	float FocusDistance = 1000.f;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
