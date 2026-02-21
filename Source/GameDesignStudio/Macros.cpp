// Fill out your copyright notice in the Description page of Project Settings.


#include "Macros.h"

void Debug::PrintToScreen(const FString& Msg, float Time, FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, Msg);
	}
}


bool Macros::CanActorSeeActor(const AActor* CheckingActor, const AActor* ActorToCheck, TArray<class AActor*> ActorsToIgnore)
{
	if (!ActorToCheck) return false;
	if (!CheckingActor) return false;
	const FVector Start =CheckingActor->GetActorLocation();
	const FVector End = ActorToCheck->GetActorLocation();
	
	
	
	FHitResult HitResult;
		
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(CheckingActor);            // Ignore self
	Params.AddIgnoredActor(ActorToCheck); //ignore the one we are checking
	if (!ActorsToIgnore.IsEmpty())
	{
		for (AActor* ActorToIgnore : ActorsToIgnore)
		{
			if (ActorToIgnore)
			{
				Params.AddIgnoredActor(ActorToIgnore);
			}
		}
	}
	Params.bTraceComplex = true;             // Use complex collision if needed
	Params.bReturnPhysicalMaterial = false;
	
	const bool bHit = CheckingActor->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility,Params );
	if (bHit)
	{
		if (HitResult.GetActor())
		{
			//Debug::PrintToScreen(HitResult.GetActor()->GetName(), 10.f, FColor::Purple);
		}else
		{
			//Debug::PrintToScreen(HitResult.ImpactPoint, 10.f, FColor::Purple);
#if !UE_BUILD_SHIPPING
			DrawDebugLine(CheckingActor->GetWorld(), Start, HitResult.ImpactPoint, FColor::Yellow, true);
			DrawDebugPoint(CheckingActor->GetWorld(), HitResult.ImpactPoint, 100.f, FColor::Purple, true);
#endif
		}
		
		return false;
	}
	//Debug::PrintToScreen("CanSeeObject");
	return true;
}