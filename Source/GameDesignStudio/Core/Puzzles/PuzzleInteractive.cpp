// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInteractive.h"

void APuzzleInteractive::Interact(APawn* Pawn) { }

bool APuzzleInteractive::IsInRange(APawn* Pawn)
{
	return ((this->GetActorTransform().GetLocation() - Pawn->GetActorTransform().GetLocation()).Size() <= InteractRange);
}