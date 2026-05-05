// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoundedPostProcess.h"
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
	FPostProcessHandle SpawnPostProcess(FTransform Transform,float Life = 0.0f, TSubclassOf<ABoundedPostProcess> SpawnClass = nullptr);

	UFUNCTION(BlueprintCallable)
	void DestroyPostProcess(FPostProcessHandle Handle);
};
