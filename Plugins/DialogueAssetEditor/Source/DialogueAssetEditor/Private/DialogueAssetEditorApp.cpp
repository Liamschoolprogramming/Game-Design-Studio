#include "DialogueAssetEditorApp.h"

#include "CompleteQuestGraphNode.h"
#include "DialogueAssetAppMode.h"
#include "DialogueAssetAppMode.h"
#include "DialogueAsset.h"
#include "DialogueCheckQuestGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueStartGraphNode.h"
#include "DialogueEndGraphNode.h"
#include "DialogueGraphSchema.h"
#include "DialogueNodeInfo.h"
#include "Kismet2/BlueprintEditorUtils.h"

DEFINE_LOG_CATEGORY_STATIC(FDialogueAssetEditorAppSub, Log, All)

void FDialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

/**
 * Setup the editor for the asset
 * 
 * @param InObject object we are editing
 */
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

	WorkingAsset->SetPreSaveListener([this] () {OnWorkingAssetPreSave();});
	
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
	
	
}
/**
 * @returns the first UDialogueGraphNode in the given selection or nullptr if there are none.
 */
class UDialogueGraphNodeBase* FDialogueAssetEditorApp::GetSelectedNode(const FGraphPanelSelectionSet& Selection)
{
	//find first UDialogueGraphNode
	for (UObject* Obj: Selection)
	{
		UDialogueGraphNodeBase* Node = Cast<UDialogueGraphNodeBase>(Obj);
		if (Node != nullptr)
		{
			
			return Node;
		}
	}
	return nullptr;
}

void FDialogueAssetEditorApp::SetSelectedNodeDetailView(TSharedPtr<class IDetailsView> DetailsView)
{
	SelectedNodeDetailView = DetailsView;
	SelectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this, &FDialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated);
}

void FDialogueAssetEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selections)
{
	UDialogueGraphNodeBase* SelectedNode = GetSelectedNode(Selections);
	if (SelectedNode != nullptr)
	{
		SelectedNodeDetailView->SetObject(SelectedNode->GetNodeInfo());
	}
}

void FDialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& ChangedEvent)
{
	if (WorkingGraphUI != nullptr)
	{
		//Get node being modified 
		UDialogueGraphNodeBase* DialogueNode = GetSelectedNode(WorkingGraphUI->GetSelectedNodes());
		if (DialogueNode != nullptr)
		{
			DialogueNode->OnPropertiesChanged();
		}
		WorkingGraphUI->NotifyGraphChanged();
	}
}

void FDialogueAssetEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	
	WorkingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void FDialogueAssetEditorApp::OnWorkingAssetPreSave()
{
	//Update our asset file from the graph before saving
	UpdateWorkingAssetFromGraph();
}

/**
 * To actually use the asset data in game as well as save it, 
 * we need to convert the WorkingGraph data to the WorkingAsset data
 * WorkingAsset is the actual file on disk; the WorkingGraph really only exists in RAM.
 */
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
			RuntimePin->Parent = RuntimeNode;
			
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
		
	
		UDialogueGraphNodeBase* UiDialogueNode = Cast<UDialogueGraphNodeBase>(UiNode);
		RuntimeNode->NodeInfo = DuplicateObject(UiDialogueNode->GetNodeInfo(), RuntimeNode);
		RuntimeNode->NodeType = UiDialogueNode->GetDialogueNodeType();
			
		
		
		RuntimeGraph->Nodes.Add(RuntimeNode);
	}
	
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UDialogueeRuntimePin* Pin1 = IdToPinMap[Connection.first];
		UDialogueeRuntimePin* Pin2 = IdToPinMap[Connection.second];
		Pin1->Connection = Pin2;
	}
}
/**
 * When we open the asset editor or load the WorkingGraph,
 * we need to make sure to try and load the data saved on disk
 * in the WorkingAsset
 */
void FDialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;
	
	for (UDialogueRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueGraphNodeBase* NewNode = nullptr;
		if (RuntimeNode->NodeType == EDialogueNodeType::StartNode)
		{
			NewNode = NewObject<UDialogueStartGraphNode>(WorkingGraph);
		} else if (RuntimeNode->NodeType == EDialogueNodeType::DialogueNode)
		{
			NewNode = NewObject<UDialogueGraphNode>(WorkingGraph);
		}else if (RuntimeNode->NodeType == EDialogueNodeType::CheckQuestsNode)
		{
			NewNode = NewObject<UDialogueCheckQuestGraphNode>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::CompleteQuestGraphNode)
		{
			NewNode = NewObject<UCompleteQuestGraphNode>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::EndNode)
		{
			NewNode = NewObject<UDialogueEndGraphNode>(WorkingGraph);
		} else
		{
			UE_LOG(FDialogueAssetEditorAppSub, Error, TEXT("FDialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset: Unknown type"));
			continue;
		}
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;
		
		if (RuntimeNode->NodeInfo != nullptr)
		{
			NewNode->SetNodeInfo(DuplicateObject(RuntimeNode->NodeInfo, NewNode));
		} else
		{
			NewNode->InitNodeInfo(NewNode);
		}
		
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
