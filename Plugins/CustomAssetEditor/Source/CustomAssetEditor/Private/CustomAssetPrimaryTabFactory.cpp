// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAssetPrimaryTabFactory.h"
#include "CustomAssetEditorApp.h"



FCustomAssetPrimaryTabFactory::FCustomAssetPrimaryTabFactory(TSharedPtr<class FCustomAssetEditorApp> InApp) : FWorkflowTabFactory(FName("CustomAssetPrimaryTab"), InApp)
{
	App = InApp;
	TabLabel =  FText::FromString("Primary");
	ViewMenuDescription = FText::FromString("Displays a primary view for whatever you want.");
	ViewMenuTooltip = FText::FromString("Shows the primary view.");
}

TSharedRef<SWidget> FCustomAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return SNew(STextBlock).Text(FText::FromString(TEXT("This is a text widget for the custom tab.")));
}

FText FCustomAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary stuff."));
}
