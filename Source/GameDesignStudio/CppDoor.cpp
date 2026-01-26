// Fill out your copyright notice in the Description page of Project Settings.


#include "CppDoor.h"

// Sets default values
ACppDoor::ACppDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACppDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACppDoor::OpenDoor()
{
	DoorMesh -> SetMaterial(0, OpenMaterial);
	bOpen = true;
}

void ACppDoor::CloseDoor()
{
	DoorMesh -> SetMaterial(0, ClosedMaterial);
	bOpen = false;
}

