// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetAppMode.h"

#include "CustomAssetEditorApp.h"
#include "CustomAssetPrimaryTabFactory.h"


FCustomAssetAppMode::FCustomAssetAppMode(TSharedPtr<class FCustomAssetEditorApp> InApp): FApplicationMode(TEXT("CustomAssetAppMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FCustomAssetPrimaryTabFactory(InApp)));

	TabLayout = FTabManager::NewLayout("CustomAssetAppMode_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()->AddTab(FName(TEXT("CustomAssetPrimaryTab")), ETabState::OpenedTab)
		)
	);
	
}

void FCustomAssetAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FCustomAssetEditorApp> AppPoint = App.Pin();
	AppPoint->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
	
}

void FCustomAssetAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FCustomAssetAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
