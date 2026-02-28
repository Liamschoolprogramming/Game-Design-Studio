// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PuzzleGriefManager.h"

//void UPuzzleGriefManager::BeginPlay()
//{
	//if (solved)
	//{
		// was going to put a thing here for when the level reloads so that the grief objects would
		// automatically disable, but
		// 1. the objects would unload and it'd need time to load them into the array before doing so (not a big issue)
		// 2. managers seem to be "overhead" and BeginPlay would likely just run once if that's the case.
		// this means that it wouldn't disable anything at all because it never runs BeginPlay after the game loads
		// for the first time.
		// for now, i'll try to solve this problem a different way
	//}
//}

void UPuzzleGriefManager::DisableAllGriefObjects()
{
	UE_LOG(LogTemp, Warning, TEXT("Attempting to disable all Grief Objects..."));
	for(int i = 0; i < GriefObjects.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Disabling Grief Object..."));
		GriefObjects[i]->DisableParticlesInBlueprint();
	}
}

void UPuzzleGriefManager::RegisterGriefActor(AGriefObject* GriefObject)
{
	if (GriefObject)
	{
		GriefObjects.Add(GriefObject);
		if (solved)
		{
			GriefObject->DisableParticlesInBlueprint();
		}
	}
}