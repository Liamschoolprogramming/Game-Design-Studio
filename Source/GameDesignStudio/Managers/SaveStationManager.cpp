// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveStationManager.h"
#include "Core/Puzzles/SaveStation.h"

#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "Engine/RendererSettings.h"
#include "Kismet/GameplayStatics.h"

void USaveStationManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	ActiveSaveStation = nullptr;
	SaveStations = GetSaveStations();
	CurrentSaveStationIndex = 0;
}

/**
 * Sets the save station that the player respawns at.
 * @param SaveStation 
 */
void USaveStationManager::SetActiveSaveStation(ASaveStation* SaveStation)
{
	SaveStations = GetSaveStations();
	
	CurrentSaveStationIndex = SaveStations.Find(SaveStation);
	ActiveSaveStation = SaveStation;
}

/**
 * @return an array of every save station in the world.
 */
TArray<ASaveStation*> USaveStationManager::GetSaveStations()
{
	TArray<ASaveStation*> Stations;

	for (TActorIterator<ASaveStation> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		Stations.Add(*Iterator);
	}

	return Stations;
}

/* *
 * Updates the players save station to be the next one in list.
*/
void USaveStationManager::NextSaveStation()
{
	SaveStations = GetSaveStations();
	if (SaveStations.Num() < 1)
	{
		return;
	}
	
	int NextIndex = CurrentSaveStationIndex+1;
	if (NextIndex >= SaveStations.Num())
	{
		NextIndex = 0;
	}
	
	SetActiveSaveStation(SaveStations[NextIndex]);
}

/* *
 * Updates the players save station to be the previous one in list.
*/
void USaveStationManager::PreviousSaveStation()
{
	SaveStations = GetSaveStations();
	if (SaveStations.Num() < 1)
	{
		return;
	}
	
	int PreviousIndex = CurrentSaveStationIndex-1;
	if (PreviousIndex < 0)
	{
		PreviousIndex = SaveStations.Num()-1;
	}
	
	SetActiveSaveStation(SaveStations[PreviousIndex]);
}
