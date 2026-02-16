// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueAssetPropertiesTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"


FDialogueAssetPropertiesTabFactory::FDialogueAssetPropertiesTabFactory(TSharedPtr<class FDialogueAssetEditorApp> InApp) : FWorkflowTabFactory(FName("DialogueAssetPropertiesTab"), InApp)
{
	App = InApp;
	TabLabel =  FText::FromString("Properties");
	ViewMenuDescription = FText::FromString("Displays a properties view for the current asset.");
	ViewMenuTooltip = FText::FromString("Shows the properties view.");
}

TSharedRef<SWidget> FDialogueAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	
	TSharedPtr<FDialogueAssetEditorApp> LocalApp = App.Pin();
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

FText FDialogueAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A properties view for the current asset."));
}
