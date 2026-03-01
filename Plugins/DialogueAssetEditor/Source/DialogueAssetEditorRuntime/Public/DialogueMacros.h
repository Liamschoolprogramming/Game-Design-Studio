#pragma once


#if !UE_BUILD_SHIPPING
namespace DialogueDebug
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


namespace DialogueMacros
{
	std::pair<FTimerDelegate&, FTimerHandle&> CreateTimer();

	template <typename UObjectTemplate, typename... VarTypes>
	std::pair<FTimerDelegate&, FTimerHandle&> CreateTimer( UObjectTemplate* InUserObject, const FName& FunctionName, float time, bool bInLoop)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(InUserObject, FunctionName);
		InUserObject->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, time, bInLoop);
		return std::pair<FTimerDelegate&, FTimerHandle&>(TimerDelegate, TimerHandle);
	}
}
