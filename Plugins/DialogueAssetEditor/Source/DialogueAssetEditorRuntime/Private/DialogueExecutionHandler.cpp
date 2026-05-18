// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueExecutionHandler.h"


// Add default functionality here for any IDialogueExecutionHandler functions that are not pure virtual.
FOnCameraChange& IDialogueExecutionHandler::GetOnCameraChanged()
{
	return OnCameraChange;
}
