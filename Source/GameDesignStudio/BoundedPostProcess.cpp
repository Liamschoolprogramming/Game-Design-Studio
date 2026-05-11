// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundedPostProcess.h"

ABoundedPostProcess::ABoundedPostProcess()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("ColisionSphere");
	RootComponent = SphereComp;
	PostProcessComponent->bUnbound = false;
	PostProcessComponent->SetupAttachment(SphereComp);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABoundedPostProcess::FadeWeight(float Speed)
{
	if (!PostProcessComponent) return;
	
	
	
	bFading = true;
	FadeSpeed = Speed;
	
}

void ABoundedPostProcess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bFading && PostProcessComponent)
	{
		
		PostProcessComponent->BlendWeight = FMath::Clamp(PostProcessComponent->BlendWeight + (FadeSpeed * DeltaTime), 0.0f, 1.0f);
		
		if (PostProcessComponent->BlendWeight == 1.0f)
		{
			bFading = false;
			FadeSpeed = 0.0f;
		}
		else if (PostProcessComponent->BlendWeight == 0.0f)
		{
			Destroy();
		}
	}
}
