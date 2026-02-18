#pragma once

#include "CoreMinimal.h"
#include "SlateIM.h"
#include "SlateIMWidgetBase.h"

class FDebugMenu;

class FDebugMenu : public FSlateIMWindowBase
{
public:
	
	FDebugMenu(const TCHAR* Command, const TCHAR* CommandHelp)
		: FSlateIMWindowBase(TEXT("Debug"), FVector2f(300, 150), Command, CommandHelp)
	{}
	
	void DrawWindow(float DeltaTime)
	{
		
	}
	
};
