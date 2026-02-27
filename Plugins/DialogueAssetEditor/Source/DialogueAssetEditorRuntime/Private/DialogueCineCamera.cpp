// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueCineCamera.h"


// Sets default values
ADialogueCineCamera::ADialogueCineCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraControl = CreateDefaultSubobject<UCameraControlComponent>("CameraControl");
	
	// Attach to root (ACameraActor has a root internally)
	if (CameraControl && RootComponent)
	{
		CameraControl->SetupAttachment(RootComponent);
	}
	
}

// Called when the game starts or when spawned
void ADialogueCineCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueCineCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

