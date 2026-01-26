// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPressurePlate.h"

#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ACppPressurePlate::ACppPressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	
	PlateMesh -> SetupAttachment(RootComponent);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision -> SetupAttachment(PlateMesh);
	SphereCollision -> SetSphereRadius(300);

	SphereCollision -> OnComponentBeginOverlap.AddDynamic(this, &ACppPressurePlate::OnPressurePlatePressed);
	SphereCollision -> OnComponentEndOverlap.AddDynamic(this, &ACppPressurePlate::OnPressurePlateReleased);
}

// Called when the game starts or when spawned
void ACppPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACppPressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACppPressurePlate::OnPressurePlatePressed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult& SweepResult)
{
	//Use this if check once PlayerCharacter is used
	
	if ( OtherActor -> IsA(APlayerCharacter::StaticClass()) && DoorRef )
	{
		
	}
	
	//Remove this if check once PlayerCharacter is used
	if (DoorRef)
	{
		DoorRef -> OpenDoor();
		PlateMesh -> SetMaterial(0, PressedMaterial);
	}
}

void ACppPressurePlate::OnPressurePlateReleased(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Use this if check once PlayerCharacter is used
	if ( OtherActor -> IsA(APlayerCharacter::StaticClass()) && DoorRef )
	{
		
	}
	
	//Remove this if check once PlayerCharacter is used
	if (DoorRef)
	{
		DoorRef -> CloseDoor();
		PlateMesh -> SetMaterial(0, DefaultMaterial);
	}
}