// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
/**
 * Handles registering tab factories and layout for the asset editor
 */
class FDialogueAssetAppMode : public FApplicationMode
{
public:
	FDialogueAssetAppMode(TSharedPtr<class FDialogueAssetEditorApp> InApp);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<class FDialogueAssetEditorApp> App;
	FWorkflowAllowedTabSet Tabs;
	
	
	
};
