// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundedPostProcess.h"

ABoundedPostProcess::ABoundedPostProcess()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("ColisionSphere");
	RootComponent = SphereComp;
	PostProcessComponent->bUnbound = false;
	PostProcessComponent->SetupAttachment(SphereComp);
}
