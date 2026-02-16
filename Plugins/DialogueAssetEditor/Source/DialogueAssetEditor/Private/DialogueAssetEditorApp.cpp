#include "DialogueAssetEditorApp.h"

#include "DialogueAssetAppMode.h"
#include "DialogueAssetAppMode.h"
#include "DialogueAsset.h"
#include "DialogueGraphNode.h"
#include "DialogueGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"

void FDialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FDialogueAssetEditorApp::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost,
	UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);
	
	WorkingAsset = Cast<UDialogueAsset>(InObject);
	
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
		WorkingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
		);

	
	
	InitAssetEditor(
		Mode,
		InToolkitHost,
		TEXT("DialogueAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true, //create standalone menu
		true, //create toolbar
		ObjectsToEdit
		);

	AddApplicationMode(TEXT("DialogueAssetAppMode"), MakeShareable(new FDialogueAssetAppMode(SharedThis(this))));

	SetCurrentMode(TEXT("DialogueAssetAppMode"));
	
	UpdateEditorGraphFromWorkingAsset();
	
	GraphChangedListenerHandle = WorkingGraph->AddOnGraphChangedHandler(
		FOnGraphChanged::FDelegate::CreateSP(this, &FDialogueAssetEditorApp::OnGraphChanged));
	
}

void FDialogueAssetEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingGraph->RemoveOnGraphChangedHandler(GraphChangedListenerHandle);
	
	FAssetEditorToolkit::OnClose();
}

void FDialogueAssetEditorApp::OnGraphChanged(const FEdGraphEditAction& EditAction)
{
	UpdateWorkingAssetFromGraph();
}

void FDialogueAssetEditorApp::UpdateWorkingAssetFromGraph()
{
	if (WorkingAsset == nullptr || WorkingGraph == nullptr)
	{
		return;
	}
	
	UDialogueRuntimeGraph* RuntimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogueeRuntimePin*> IdToPinMap;
	
	for (UEdGraphNode* UiNode : WorkingGraph->Nodes)
	{
		UDialogueRuntimeNode* RuntimeNode = NewObject<UDialogueRuntimeNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(UiNode->NodePosX, UiNode->NodePosY);
		
		for (UEdGraphPin* UiPin : UiNode->Pins)
		{
			UDialogueeRuntimePin* RuntimePin = NewObject<UDialogueeRuntimePin>(RuntimeNode);
			RuntimePin->PinName = UiPin->PinName;
			RuntimePin->PinId = UiPin->PinId;
			
			if (UiPin->HasAnyConnections() && UiPin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> connection = std::make_pair(UiPin->PinId, UiPin->LinkedTo[0]->PinId);
				Connections.Add(connection);
			}
			
			IdToPinMap.Add(UiPin->PinId, RuntimePin);
			if (UiPin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			} else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}
		
		RuntimeGraph->Nodes.Add(RuntimeNode);
	}
	
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UDialogueeRuntimePin* Pin1 = IdToPinMap[Connection.first];
		UDialogueeRuntimePin* Pin2 = IdToPinMap[Connection.second];
		Pin1->Connection = Pin2;
	}
}

void FDialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;
	
	for (UDialogueRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueGraphNode* NewNode = NewObject<UDialogueGraphNode>(WorkingGraph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;
		
		if (RuntimeNode->InputPin != nullptr)
		{
			UDialogueeRuntimePin* Pin = RuntimeNode->InputPin;
			UEdGraphPin* UiPin = NewNode->CreateDialoguePin(EGPD_Input, Pin->PinName);
			UiPin->PinId = Pin->PinId;
			
			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(UiPin->PinId, Pin->Connection->PinId));
			}
			IdToPinMap.Add(Pin->PinId, UiPin);
		}
		
		for (UDialogueeRuntimePin* Pin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* UiPin = NewNode->CreateDialoguePin(EGPD_Output, Pin->PinName);
			UiPin->PinId = Pin->PinId;
			
			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(UiPin->PinId, Pin->Connection->PinId));
			}
			IdToPinMap.Add(Pin->PinId, UiPin);
		}
		
		WorkingGraph->AddNode(NewNode, true, true);
	}
	
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UEdGraphPin* FromPin = IdToPinMap[Connection.first];
		UEdGraphPin* ToPin = IdToPinMap[Connection.second];
		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
}
