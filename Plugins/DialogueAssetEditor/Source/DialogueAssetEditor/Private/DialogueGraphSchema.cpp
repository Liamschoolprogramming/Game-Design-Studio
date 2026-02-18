#include "DialogueGraphSchema.h"

#include "DialogueEndGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueStartGraphNode.h"
#include "DialogueNodeInfo.h"

//this defines actions on nodes

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewDialogueNodeAction(
		new FNewNodeAction(
			UDialogueGraphNode::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Node")),
			FText::FromString(TEXT("Makes a new dialogue node")),
			0)
			);
	
	TSharedPtr<FNewNodeAction> NewEndNodeAction(
		new FNewNodeAction(
			UDialogueEndGraphNode::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New End Node")),
			FText::FromString(TEXT("Makes a new end node")),
			0)
			);
	
	ContextMenuBuilder.AddAction(NewDialogueNodeAction);
	ContextMenuBuilder.AddAction(NewEndNodeAction);
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Need two pins"));
	}
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
	
}

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UDialogueStartGraphNode* StartNode = NewObject<UDialogueStartGraphNode>(&Graph);
	StartNode->CreateNewGuid();
	StartNode->NodePosX = 0;
	StartNode->NodePosY = 0;
	
	StartNode->CreateDialoguePin(EGPD_Output, TEXT("Start"));
	
	Graph.AddNode(StartNode, true, true);
	Graph.Modify();
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,const FVector2f& Location, bool bSelectNewNode)
{
	UDialogueGraphNodeBase* Result = NewObject<UDialogueGraphNodeBase>(ParentGraph, ClassTemplate);
	Result->CreateNewGuid();
	
	Result->NodePosX = Location.X;
	Result->NodePosY = Location.Y;
	
	Result->InitNodeInfo(Result);
	
	UEdGraphPin* InputPin = Result->CreateDefaultInputPin();
	Result->CreateDefaultOutputPins();
	
	
	if (FromPin != nullptr)
	{
		Result->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}
	
	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);
	
	
	return Result;
	
}
