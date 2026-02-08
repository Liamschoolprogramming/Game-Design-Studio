// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Puzzles/Pickups/MirrorGolem.h"
#include "PossessableEntity.h"
#include "PosessableEntity.cpp"

// Sets default values
AMirrorGolem::AMirrorGolem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMirrorGolem::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void AMirrorGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMirrorGolem::OnTogglePossession()
{
	if (bPossessed)
	{
		PlayerController->Possess(PlayerCharacter);
		bPossessed = false;
	}
	else
	{
		PlayerController->Possess(this);
		bPossessed = true;
	}
}

void AMirrorGolem::OnPossess()
{
	PlayerController->Possess(this);
	
	
	bPossessed = true;
}

void AMirrorGolem::OnCancelPossess()
{
	PlayerController->Possess(PlayerCharacter);
	bPossessed = false;
}
