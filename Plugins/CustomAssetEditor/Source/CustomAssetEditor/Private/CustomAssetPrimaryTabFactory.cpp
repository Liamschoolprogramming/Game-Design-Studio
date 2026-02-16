// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetPrimaryTabFactory.h"
#include "CustomAssetEditorApp.h"
#include "CustomAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"


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
	
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SGraphEditor)
			.IsEditable(true)
			.GraphToEdit(LocalApp->GetWorkingGraph())
		];
	
}

FText FCustomAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary stuff."));
}
