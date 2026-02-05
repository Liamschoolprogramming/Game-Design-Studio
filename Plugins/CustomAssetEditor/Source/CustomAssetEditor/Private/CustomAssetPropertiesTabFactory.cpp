// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetPropertiesTabFactory.h"
#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"


FCustomAssetPropertiesTabFactory::FCustomAssetPropertiesTabFactory(TSharedPtr<class FCustomAssetEditorApp> InApp) : FWorkflowTabFactory(FName("CustomAssetPropertiesTab"), InApp)
{
	App = InApp;
	TabLabel =  FText::FromString("Properties");
	ViewMenuDescription = FText::FromString("Displays a properties view for the current asset.");
	ViewMenuTooltip = FText::FromString("Shows the properties view.");
}

TSharedRef<SWidget> FCustomAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FCustomAssetEditorApp> LocalApp = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(FName("PropertyEditor"));
	
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(STextBlock)
			.Text(FText::FromString(LocalApp->GetWorkingAsset()->SomeData))
		];
}

FText FCustomAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A properties view for the current asset."));
}
