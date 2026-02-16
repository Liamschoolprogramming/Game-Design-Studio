#include "CustomAssetEditorApp.h"

#include "CustomAssetAppMode.h"
#include "CustomAssetAppMode.h"
#include "CustomAsset.h"
#include "CustomGraphNode.h"
#include "CustomGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"

void FCustomAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FCustomAssetEditorApp::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost,
	UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);
	
	WorkingAsset = Cast<UCustomAsset>(InObject);
	
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
		WorkingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UCustomGraphSchema::StaticClass()
		);

	
	
	InitAssetEditor(
		Mode,
		InToolkitHost,
		TEXT("CustomAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true, //create standalone menu
		true, //create toolbar
		ObjectsToEdit
		);

	AddApplicationMode(TEXT("CustomAssetAppMode"), MakeShareable(new FCustomAssetAppMode(SharedThis(this))));

	SetCurrentMode(TEXT("CustomAssetAppMode"));
	
	UpdateEditorGraphFromWorkingAsset();
	
	GraphChangedListenerHandle = WorkingGraph->AddOnGraphChangedHandler(
		FOnGraphChanged::FDelegate::CreateSP(this, &FCustomAssetEditorApp::OnGraphChanged));
	
}

void FCustomAssetEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingGraph->RemoveOnGraphChangedHandler(GraphChangedListenerHandle);
	
	FAssetEditorToolkit::OnClose();
}

void FCustomAssetEditorApp::OnGraphChanged(const FEdGraphEditAction& EditAction)
{
	UpdateWorkingAssetFromGraph();
}

void FCustomAssetEditorApp::UpdateWorkingAssetFromGraph()
{
	if (WorkingAsset == nullptr || WorkingGraph == nullptr)
	{
		return;
	}
	
	UCustomRuntimeGraph* RuntimeGraph = NewObject<UCustomRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UCustomeRuntimePin*> IdToPinMap;
	
	for (UEdGraphNode* UiNode : WorkingGraph->Nodes)
	{
		UCustomRuntimeNode* RuntimeNode = NewObject<UCustomRuntimeNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(UiNode->NodePosX, UiNode->NodePosY);
		
		for (UEdGraphPin* UiPin : UiNode->Pins)
		{
			UCustomeRuntimePin* RuntimePin = NewObject<UCustomeRuntimePin>(RuntimeNode);
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
		UCustomeRuntimePin* Pin1 = IdToPinMap[Connection.first];
		UCustomeRuntimePin* Pin2 = IdToPinMap[Connection.second];
		Pin1->Connection = Pin2;
	}
}

void FCustomAssetEditorApp::UpdateEditorGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;
	
	for (UCustomRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UCustomGraphNode* NewNode = NewObject<UCustomGraphNode>(WorkingGraph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;
		
		if (RuntimeNode->InputPin != nullptr)
		{
			UCustomeRuntimePin* Pin = RuntimeNode->InputPin;
			UEdGraphPin* UiPin = NewNode->CreateCustomPin(EGPD_Input, Pin->PinName);
			UiPin->PinId = Pin->PinId;
			
			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(UiPin->PinId, Pin->Connection->PinId));
			}
			IdToPinMap.Add(Pin->PinId, UiPin);
		}
		
		for (UCustomeRuntimePin* Pin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* UiPin = NewNode->CreateCustomPin(EGPD_Output, Pin->PinName);
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
