// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraAttachPoint.h"
#include "UObject/Interface.h"
#include "PlayerCharacterCameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPlayerCharacterCameraInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEDESIGNSTUDIO_API IPlayerCharacterCameraInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UCameraAttachPoint* GetAttachPoint()
	{
		return nullptr;
	}
};
