// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInteractive.h"
#include "PlayerCharacter.h"
#include "Core/Managers/GameManagerBase.h"
#include "Core/Subsystems/GameManagerSubsystem.h"


void APuzzleInteractive::Interact(APlayerCharacter* PlayerCharacter) { }

bool APuzzleInteractive::IsInRange(APlayerCharacter* PlayerCharacter)
{
	const FPlayerStats PlayerStats = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager().PlayerStats;
	return ((this->GetActorTransform().GetLocation() - PlayerCharacter->GetActorTransform().GetLocation()).Size() <= PlayerStats.InteractRange);
}