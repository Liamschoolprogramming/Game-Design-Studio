// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

void UQuestManager::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Super::Initialize(InstanceOwner);
	
	Quests = {
		{"TestItem", FQuest("Test Quest", "TestItem", 10)},
	};
}