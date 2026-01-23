// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerBase.h"
#include "GameManagerSubsystem.h"

void UGameManagerBase::Initialize(UGameManagerSubsystem* InstanceOwner)
{
	Owner = InstanceOwner;
}

void UGameManagerBase::PostInitialize()
{
	
}

void UGameManagerBase::Shutdown()
{
	
}

