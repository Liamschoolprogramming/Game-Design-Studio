// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableEntity.h"
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APossessableEntity::APossessableEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APossessableEntity::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void APossessableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APossessableEntity::OnTogglePossession()
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

void APossessableEntity::OnPossess()
{
	PlayerController->Possess(this);
	bPossessed = true;
}

void APossessableEntity::OnCancelPossess()
{
	PlayerController->Possess(PlayerCharacter);
	bPossessed = false;
}
