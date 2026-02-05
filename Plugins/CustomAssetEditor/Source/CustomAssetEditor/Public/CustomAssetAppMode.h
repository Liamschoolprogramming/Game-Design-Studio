// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
/**
 * 
 */
class FCustomAssetAppMode : public FApplicationMode
{
public:
	FCustomAssetAppMode(TSharedPtr<class FCustomAssetEditorApp> InApp);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<class FCustomAssetEditorApp> App;
	FWorkflowAllowedTabSet Tabs;
	
	
	
};
