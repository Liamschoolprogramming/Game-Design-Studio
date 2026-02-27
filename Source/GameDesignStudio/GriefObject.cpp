// Fill out your copyright notice in the Description page of Project Settings.


#include "GriefObject.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/PuzzleGriefManager.h"

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
	// this is very poor implementation. I will fix it later.
	// for now though, this does work. the function "RegisterGriefActor" can also be called in Blueprint
	// if for some reason that is necessary (it likely will because I am not very familiar with c++ unfortunately)
	UPuzzleGriefManager* CurGriefManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPuzzleGriefManager();
	CurGriefManager->RegisterGriefActor(this);
}

void AGriefObject::DisableParticlesInBlueprint()
{
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("DisableGrief"));
	if (BlueprintActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("This Grief Object should be disabled."));
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

