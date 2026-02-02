// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
namespace Debug
{
	template<typename T>
concept HasToString = requires(T a)
	{
		{ a.ToString() } -> std::convertible_to<FString>;
	} && !std::is_same_v<T, FString>;
	
	
	void PrintToScreen(const FString& Msg, float Time = 1.0f, FColor Color = FColor::Green);
	
	
	template<typename T>
	void PrintToScreen(const T& Value, float Time = 1.0f, FColor Color = FColor::Green)
	{
		if constexpr (HasToString<T>)
		{
			PrintToScreen(Value.ToString(), Time, Color);
		}
		else
		{
			PrintToScreen(FString(LexToString(Value)), Time, Color);
		}
	}
}


class GAMEDESIGNSTUDIO_API Macros
{
public:
	Macros();
	
	
	
	~Macros();
};
