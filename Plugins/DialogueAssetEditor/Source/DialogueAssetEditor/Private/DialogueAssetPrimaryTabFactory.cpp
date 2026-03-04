// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

//This is our graph editor tab

FDialogueAssetPrimaryTabFactory::FDialogueAssetPrimaryTabFactory(TSharedPtr<class FDialogueAssetEditorApp> InApp) : FWorkflowTabFactory(FName("DialogueAssetPrimaryTab"), InApp)
{
	App = InApp;
	TabLabel =  FText::FromString("Primary");
	ViewMenuDescription = FText::FromString("Displays a primary view for whatever you want.");
	ViewMenuTooltip = FText::FromString("Shows the primary view.");
}

TSharedRef<SWidget> FDialogueAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	
	TSharedPtr<FDialogueAssetEditorApp> LocalApp = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(FName("PropertyEditor"));
	
	SGraphEditor::FGraphEditorEvents GraphEvents;
	GraphEvents.OnSelectionChanged.BindRaw(LocalApp.Get(), &FDialogueAssetEditorApp::OnGraphSelectionChanged);
	
	TSharedPtr<SGraphEditor> GraphEditor =
		SNew(SGraphEditor)
		.IsEditable(true)
		.GraphEvents(GraphEvents)
		.GraphToEdit(LocalApp->GetWorkingGraph());
	
	LocalApp->SetWorkingGraphUI(GraphEditor);
	
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			GraphEditor.ToSharedRef()
		];
	
}

FText FDialogueAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary stuff."));
}
