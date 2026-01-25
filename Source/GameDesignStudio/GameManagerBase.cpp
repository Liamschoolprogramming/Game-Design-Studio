// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerBase.h"
#include "GameManagerSubsystem.h"

void UGameManagerBase::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	// This is where we are passing in the subsystem
	Owner = InstanceOwner;
}

void UGameManagerBase::PostInitialize()
{
	
}

void UGameManagerBase::Shutdown()
{
	
}

