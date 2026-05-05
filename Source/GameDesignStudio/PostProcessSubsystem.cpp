// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProcessSubsystem.h"


FPostProcessHandle UPostProcessSubsystem::SpawnPostProcess(FTransform Transform,float Life, TSubclassOf<ABoundedPostProcess> SpawnClass)
{
	if (!SpawnClass) return FPostProcessHandle::Invalid();
	if (!GetWorld()) return FPostProcessHandle::Invalid();
	if (Life == 0.0f)
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();

		FActorSpawnParameters SpawnParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,Transform, SpawnParams);
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);
		return PostProcessHandle;
	}
	else
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();
		FActorSpawnParameters SpawnParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,Transform, SpawnParams);
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);

		FTimerHandle NewHandle;
		FTimerDelegate Delegate;
		Delegate.BindLambda([this, PostProcessHandle]()
		{
			DestroyPostProcess(PostProcessHandle);
		});
		
		GetWorld()->GetTimerManager().SetTimer(
		NewHandle,
		Delegate,
		Life,
		false // looping
	);
		TimerHandles.Add(PostProcessHandle.HandleID, NewHandle);
		return PostProcessHandle;
	}
}

void UPostProcessSubsystem::DestroyPostProcess(FPostProcessHandle Handle)
{
	TObjectPtr<ABoundedPostProcess> PostProcess = *ActivePostProcessInstances.Find(Handle.HandleID);
	TimerHandles.FindAndRemoveChecked(Handle.HandleID);
	if (PostProcess)
	{
		
		ActivePostProcessInstances.Remove(Handle.HandleID);
		PostProcess->Destroy();
	}
}
