// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoundedPostProcess.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PostProcessSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FPostProcessSpawnParams
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	bool bAttachToActor;
	UPROPERTY(BlueprintReadWrite)
	float Life = 0.0f;
	UPROPERTY(BlueprintReadWrite)
	AActor* OwningActor;
	UPROPERTY(BlueprintReadWrite)
	FTransform Transform = FTransform::Identity;
	UPROPERTY(BlueprintReadWrite)
	bool bFadeIn;
	UPROPERTY(BlueprintReadWrite)
	bool bFadeOut;
	UPROPERTY(BlueprintReadWrite)
	float FadeSpeed;
};


USTRUCT(BlueprintType)
struct FPostProcessHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 HandleID = INDEX_NONE;
	UPROPERTY(BlueprintReadOnly)
	FPostProcessSpawnParams SpawnParams;

	bool IsValid() const { return HandleID != INDEX_NONE; }
	static FPostProcessHandle Invalid() { return FPostProcessHandle(); }

	static FPostProcessHandle Generate()
	{
		static int32 Counter = 0;
		FPostProcessHandle NewHandle;
		NewHandle.HandleID = FPlatformAtomics::InterlockedIncrement(&Counter);
		return NewHandle;
	}
	
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
	TMap<int32, TObjectPtr<ABoundedPostProcess>> ActivePostProcessInstances;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<int32, FTimerHandle> TimerHandles;
	
	
	
	UFUNCTION(BlueprintCallable)
	FPostProcessHandle SpawnPostProcess(TSubclassOf<ABoundedPostProcess> SpawnClass, FPostProcessSpawnParams SpawnParams);

	UFUNCTION(BlueprintCallable)
	void DestroyPostProcess(FPostProcessHandle Handle);
};
