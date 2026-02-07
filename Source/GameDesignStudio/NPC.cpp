// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

ANPC::ANPC()
{
	DialogueActorComponent = CreateDefaultSubobject<UDialogueActorComponent>(TEXT("DialogueActorComponent"));
	if (DialogueActorComponent)
	{
		DialogueActorComponent->NPCName = NPCName;
	}
}
