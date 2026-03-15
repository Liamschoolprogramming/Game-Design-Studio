// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialManager.h"

#include "Blueprint/UserWidget.h"
#include "Core/Subsystems/GameManagerSubsystem.h"

void UTutorialManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	TutorialProgress = {};
}

/**
 * @param Tutorial 
 * @return Current Stage of the requested Tutorial.
 */
ETutorialStage UTutorialManager::GetCurrentStage(FName Tutorial)
{
	return TutorialProgress.FindRef(Tutorial);
}

/**
 * @param Tutorial 
 * @return Whether the given tutorial has been completed.
 */
bool UTutorialManager::IsComplete(FName Tutorial)
{
	return TutorialProgress.FindRef(Tutorial) == ETutorialStage::Completed;
}

/**
 * Sets the progress for the given tutorial.
 * @param Tutorial 
 */
void UTutorialManager::SetTutorialStage(FName Tutorial, ETutorialStage Stage)
{
	TutorialProgress.Add(Tutorial, Stage);
}


