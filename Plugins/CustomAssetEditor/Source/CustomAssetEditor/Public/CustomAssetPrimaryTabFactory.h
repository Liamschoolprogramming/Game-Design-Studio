// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
/**
 * 
 */
class  FCustomAssetPrimaryTabFactory : public FWorkflowTabFactory
{
public:
	FCustomAssetPrimaryTabFactory(TSharedPtr<class FCustomAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<class FCustomAssetEditorApp> App;
	
};
