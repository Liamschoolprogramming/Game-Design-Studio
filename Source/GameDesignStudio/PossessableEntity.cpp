// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableEntity.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APossessableEntity::APossessableEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APossessableEntity::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	OnClicked.AddDynamic(this, );
	
}

// Called every frame
void APossessableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APossessableEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

