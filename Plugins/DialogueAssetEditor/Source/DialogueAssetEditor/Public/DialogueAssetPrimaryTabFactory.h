// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
/**
 * 
 */
class  FDialogueAssetPrimaryTabFactory : public FWorkflowTabFactory
{
public:
	FDialogueAssetPrimaryTabFactory(TSharedPtr<class FDialogueAssetEditorApp> InApp);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<class FDialogueAssetEditorApp> App;
	
};
