// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PuzzleGriefManager.h"

void UPuzzleGriefManager::DisableAllGriefObjects()
{
	for(int i = 0; i < GriefObjects.Num(); i++)
	{
		GriefObjects[i]->DisableParticlesInBlueprint();
	}
}

void UPuzzleGriefManager::RegisterGriefActor(AGriefObject* GriefObject)
{
	if (GriefObject)
	{
		GriefObjects.Add(GriefObject);
	}
}