// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInteractive.h"
#include "PlayerCharacter.h"

void APuzzleInteractive::Interact(APlayerCharacter* PlayerCharacter) { }

bool APuzzleInteractive::IsInRange(APlayerCharacter* PlayerCharacter)
{
	return ((this->GetActorTransform().GetLocation() - PlayerCharacter->GetActorTransform().GetLocation()).Size() <= InteractRange);
}