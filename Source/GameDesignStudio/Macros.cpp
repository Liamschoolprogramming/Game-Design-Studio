// Fill out your copyright notice in the Description page of Project Settings.


#include "Macros.h"

Macros::Macros()
{
}

void Debug::PrintToScreen(const FString& Msg, float Time, FColor Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, Msg);
	}
}

Macros::~Macros()
{
}
