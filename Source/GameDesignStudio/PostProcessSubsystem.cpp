// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProcessSubsystem.h"


FPostProcessHandle UPostProcessSubsystem::SpawnPostProcess(TSubclassOf<ABoundedPostProcess> SpawnClass, FPostProcessSpawnParams SpawnParams)
{
	if (!SpawnClass) return FPostProcessHandle::Invalid();
	if (!GetWorld()) return FPostProcessHandle::Invalid();
	
	
	
	if (SpawnParams.Life == 0.0f)
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();
		PostProcessHandle.SpawnParams = SpawnParams;

		FActorSpawnParameters SpawnActorParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,SpawnParams.Transform, SpawnActorParams);
		if (SpawnParams.bFadeIn)
		{
			UE_LOG(LogTemp, Log, TEXT("FadeIn"));
			NewPostProcess->FadeWeight(SpawnParams.FadeSpeed);
		}
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);
		if (SpawnParams.bAttachToActor && SpawnParams.OwningActor)
		{
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	
			NewPostProcess->AttachToActor(SpawnParams.OwningActor, AttachmentTransformRules);
		}
		return PostProcessHandle;
	}
	else
	{
		FPostProcessHandle PostProcessHandle = FPostProcessHandle::Generate();
		PostProcessHandle.SpawnParams = SpawnParams;

		FActorSpawnParameters SpawnActorParams;
		ABoundedPostProcess* NewPostProcess = GetWorld()->SpawnActor<ABoundedPostProcess>(SpawnClass,SpawnParams.Transform, SpawnActorParams);
		ActivePostProcessInstances.Add(PostProcessHandle.HandleID, NewPostProcess);
		if (SpawnParams.bFadeIn)
		{
			UE_LOG(LogTemp, Log, TEXT("FadeIn"));
			NewPostProcess->FadeWeight(SpawnParams.FadeSpeed);
		}
		if (SpawnParams.bAttachToActor && SpawnParams.OwningActor)
		{
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	
			NewPostProcess->AttachToActor(SpawnParams.OwningActor, AttachmentTransformRules);
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
		SpawnParams.Life,
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
    
	if (PostProcess->Get())
	{
		if (Handle.SpawnParams.bFadeOut)
		{
			UE_LOG(LogTemp, Log, TEXT("FadeOut"));
			PostProcess->Get()->FadeWeight(Handle.SpawnParams.FadeSpeed * -1);
		}
		else
		{
			(*PostProcess)->Destroy();
		}
		
	}
}
