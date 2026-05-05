// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnablePostProcess.h"

// Sets default values
ASpawnablePostProcess::ASpawnablePostProcess()
{
	PrimaryActorTick.bCanEverTick = false;

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	RootComponent = PostProcessComponent;

}

// Called when the game starts or when spawned
void ASpawnablePostProcess::BeginPlay()
{
	Super::BeginPlay();
	
	
}

