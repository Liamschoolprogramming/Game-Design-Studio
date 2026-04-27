// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PostProcessSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FPostProcessHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 HandleID = INDEX_NONE;

	bool IsValid() const { return HandleID != INDEX_NONE; }
	static FPostProcessHandle Invalid() { return FPostProcessHandle(); }
};


/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UPostProcessSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<class ASpawnablePostProcess*> ActivePostProcessInstances;
	
	
	
	UFUNCTION(BlueprintCallable)
	void SpawnPostProcess(float Life = 0.0f, ASpawnablePostProcess* SpawnInstance = nullptr);
};
