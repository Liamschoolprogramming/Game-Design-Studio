// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetPrimaryTabFactory.h"
#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"


FCustomAssetPrimaryTabFactory::FCustomAssetPrimaryTabFactory(TSharedPtr<class FCustomAssetEditorApp> InApp) : FWorkflowTabFactory(FName("CustomAssetPrimaryTab"), InApp)
{
	App = InApp;
	TabLabel =  FText::FromString("Primary");
	ViewMenuDescription = FText::FromString("Displays a primary view for whatever you want.");
	ViewMenuTooltip = FText::FromString("Shows the primary view.");
}

TSharedRef<SWidget> FCustomAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FCustomAssetEditorApp> LocalApp = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(FName("PropertyEditor"));
	
	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = false; 
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.NotifyHook = nullptr;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = false;
		DetailsViewArgs.bShowScrollBar = false;
	}
	
	TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(LocalApp->GetWorkingAsset());
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			DetailsView.ToSharedRef()
		];
}

FText FCustomAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary stuff."));
}
