// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameManagerBase.generated.h"

/**
 * 
 */

class UGameManagerSubsystem;

UCLASS(Abstract, Blueprintable)
class GAMEDESIGNSTUDIO_API UGameManagerBase : public UObject
{
	GENERATED_BODY()
public:
	
	// Sets the owning subsystem
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner);
	
	virtual void Shutdown();
	
	virtual void PostInitialize();
	
protected:
	
	// On each manager initialization, it adds itself to this array
	UPROPERTY()
	TObjectPtr<UGameManagerSubsystem> Owner;
	
};
