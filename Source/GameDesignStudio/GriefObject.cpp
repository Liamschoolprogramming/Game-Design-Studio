// Fill out your copyright notice in the Description page of Project Settings.


#include "GriefObject.h"

// Sets default values
AGriefObject::AGriefObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGriefObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGriefObject::DisableParticlesInBlueprint()
{
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("DisableGrief"));
	if (BlueprintActor)
	{
		BlueprintActor->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	}
}

void AGriefObject::EnableParticlesInBlueprint()
{
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("EnableGrief"));
	if (BlueprintActor)
	{
		BlueprintActor->CallFunctionByNameWithArguments(*command, ar, NULL, true);
	}
}

// Called every frame
void AGriefObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

