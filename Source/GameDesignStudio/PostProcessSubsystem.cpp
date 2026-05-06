// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProcessSubsystem.h"


FPostProcessHandle UPostProcessSubsystem::SpawnPostProcess(FTransform Transform, float Life, TSubclassOf<ABoundedPostProcess> SpawnClass, bool bAttachToActor, AActor* OwningActor)
{
	if (!SpawnClass) return FPostProcessHandle::Invalid();
	if (!GetWorld()) return FPostProcessHandle::Invalid();
	
	if (Life == 0.0f)
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();

		FActorSpawnParameters SpawnParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,Transform, SpawnParams);
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);
		if (bAttachToActor && OwningActor)
		{
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	
			NewPostProcess->AttachToActor(OwningActor, AttachmentTransformRules);
		}
		return PostProcessHandle;
	}
	else
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();
		FActorSpawnParameters SpawnParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,Transform, SpawnParams);
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);

		if (bAttachToActor && OwningActor)
		{
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	
			NewPostProcess->AttachToActor(OwningActor, AttachmentTransformRules);
		}
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
	TObjectPtr<ABoundedPostProcess>* PostProcess = ActivePostProcessInstances.Find(Handle.HandleID);
	if (!PostProcess) return;

	if (FTimerHandle* Timer = TimerHandles.Find(Handle.HandleID))
	{
		GetWorld()->GetTimerManager().ClearTimer(*Timer);
		TimerHandles.Remove(Handle.HandleID);
	}

	ActivePostProcessInstances.Remove(Handle.HandleID);
    
	if ((*PostProcess)->IsValidLowLevel())
	{
		(*PostProcess)->Destroy();
	}
}
