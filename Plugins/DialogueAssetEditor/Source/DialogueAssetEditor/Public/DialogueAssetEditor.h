// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"

class FDialogueAssetEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:
	TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
	TSharedPtr<struct FDialoguePinFactory> DialoguePinFactory = nullptr;
};
