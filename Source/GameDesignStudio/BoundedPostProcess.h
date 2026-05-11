// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnablePostProcess.h"
#include "Components/SphereComponent.h"
#include "BoundedPostProcess.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API ABoundedPostProcess : public ASpawnablePostProcess
{
	
	GENERATED_BODY()

	
public:
	ABoundedPostProcess();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* SphereComp;
	
	UFUNCTION(BlueprintCallable)
	void FadeWeight(float Speed);
	
	virtual void Tick(float DeltaTime) override;
	
	private:
	bool bFading;
	float FadeSpeed;
	
};
