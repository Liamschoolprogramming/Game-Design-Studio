// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Components/CapsuleComponent.h"

ANPC::ANPC()
{
	
	
	
	
	GetCapsuleComponent()->ComponentTags.Empty();
	GetCapsuleComponent()->ComponentTags.Add("HitBox");
	
}
