// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedPlayerComponent.h"

#include "PlayerControllerBase.h"
#include "Core/Subsystems/SaveSubsystem.h"


// Sets default values for this component's properties
USavedPlayerComponent::USavedPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USavedPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	USaveSubsystem* SaveSubsystem = GetOwner()->GetGameInstance()->GetSubsystem<USaveSubsystem>();
	if (SaveSubsystem)
	{
		FPlayerData PlayerData = SaveSubsystem->LoadPlayer();
		if (PlayerData.PlayerLocation != FVector(0,0,0))
		{
			GetOwner()->SetActorLocation(PlayerData.PlayerLocation);
		}
		if (PlayerData.PlayerRotation != FRotator(-180,-180,-180))
		{
			GetOwner()->SetActorRotation(PlayerData.PlayerRotation);
		}
		if (PlayerData.UnlockedPossessables.Num() > 0)
		{
			if (APlayerControllerBase* PlayerControllerBase = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController()))
			{
				for (auto Possesable : PlayerData.UnlockedPossessables)
				{
					PlayerControllerBase->UnlockPossession(Possesable);
				}
			}
		}
	
	}
	
}


// Called every frame
void USavedPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

