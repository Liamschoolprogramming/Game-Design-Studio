// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueAssetAppMode.h"

#include "DialogueAssetEditorApp.h"
#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetPropertiesTabFactory.h"

FDialogueAssetAppMode::FDialogueAssetAppMode(TSharedPtr<class FDialogueAssetEditorApp> InApp): FApplicationMode(TEXT("DialogueAssetAppMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDialogueAssetPrimaryTabFactory(InApp)));
	Tabs.RegisterFactory(MakeShareable(new FDialogueAssetPropertiesTabFactory(InApp)));
	

	TabLayout = FTabManager::NewLayout("DialogueAssetAppMode_Layout_v1")
	->AddArea
	(
		
		FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split //add child
			(
				FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
						FTabManager::NewStack()
							->SetSizeCoefficient(0.75)
							->AddTab(FName(TEXT("DialogueAssetPrimaryTab")), ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
							->SetSizeCoefficient(0.25)
							->AddTab(FName(TEXT("DialogueAssetPropertiesTab")), ETabState::OpenedTab)
					)
			)
	);
	
	
}

void FDialogueAssetAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FDialogueAssetEditorApp> AppPoint = App.Pin();
	AppPoint->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
	
}

void FDialogueAssetAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDialogueAssetAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
