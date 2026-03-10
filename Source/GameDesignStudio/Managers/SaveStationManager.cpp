// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveStationManager.h"
#include "Core/Puzzles/SaveStation.h"

#include "Macros.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Engine/RendererSettings.h"
#include "Kismet/GameplayStatics.h"

void USaveStationManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	ActiveSaveStation = nullptr;
}

