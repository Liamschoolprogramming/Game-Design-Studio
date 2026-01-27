// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInteractive.h"
#include "Components/SphereComponent.h"

APuzzleInteractive::APuzzleInteractive()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(BaseMesh);
	SphereCollision->SetSphereRadius(100.f);
}