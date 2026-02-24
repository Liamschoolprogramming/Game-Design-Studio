// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#if !UE_BUILD_SHIPPING
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
	
	// Overload: only override time
	template<typename T>
	void PrintToScreen(const T& Value, float Time)
	{
		PrintToScreen(Value, Time, FColor::Green);
	}

	// Overload: only override color
	template<typename T>
	void PrintToScreen(const T& Value, FColor Color)
	{
		PrintToScreen(Value, 1.0f, Color);
	}
	
	
}
#else
namespace Debug
{
	template<typename... Args>
	void PrintToScreen(Args&&...) {}
}
#endif

namespace Macros
{
	
	bool CanActorSeeActor(const class AActor* CheckingActor, const class AActor* ActorToCheck, TArray<class AActor*> ActorsToIgnore = TArray<class AActor*>());
}
