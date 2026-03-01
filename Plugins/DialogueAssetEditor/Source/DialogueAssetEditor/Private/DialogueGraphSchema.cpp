#include "DialogueGraphSchema.h"

#include "CompleteQuestGraphNode.h"
#include "DialogueCheckQuestGraphNode.h"
#include "DialogueCheckQuestNodeInfo.h"
#include "DialogueEndGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueStartGraphNode.h"
#include "DialogueNodeInfo.h"
#include "QuestProgressGraphNode.h"
#include "RandomDialogueGraphNode.h"
#include "StartQuestGraphNode.h"

//this defines actions on nodes

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewDialogueNodeAction(
		new FNewNodeAction(
			UDialogueGraphNode::StaticClass(),
			FText::FromString(TEXT("Dialogue")),
			FText::FromString(TEXT("New Node")),
			FText::FromString(TEXT("Makes a new dialogue node")),
			0)
			);
	TSharedPtr<FNewNodeAction> NewRandomDialogueNodeAction(
		new FNewNodeAction(
			URandomDialogueGraphNode::StaticClass(),
			FText::FromString(TEXT("Dialogue")),
			FText::FromString(TEXT("New Random Dialogue Node")),
			FText::FromString(TEXT("Makes a new random dialogue node")),
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
	TSharedPtr<FNewNodeAction> NewCheckQuestNodeAction(
		new FNewNodeAction(
			UDialogueCheckQuestGraphNode::StaticClass(),
			FText::FromString(TEXT("Quests")),
			FText::FromString(TEXT("New Check Quest Node")),
			FText::FromString(TEXT("Makes a new branching node that checks a quest.")),
			0)
			);
	TSharedPtr<FNewNodeAction> NewCompleteQuestNodeAction(
		new FNewNodeAction(
			UCompleteQuestGraphNode::StaticClass(),
			FText::FromString(TEXT("Quests")),
			FText::FromString(TEXT("New Complete Quest Node")),
			FText::FromString(TEXT("Makes a new node that completes a given quest.")),
			0)
			);
	TSharedPtr<FNewNodeAction> NewStartQuestNodeAction(
		new FNewNodeAction(
			UStartQuestGraphNode::StaticClass(),
			FText::FromString(TEXT("Quests")),
			FText::FromString(TEXT("New Start Quest Node")),
			FText::FromString(TEXT("Makes a new node that starts a given quest.")),
			0)
			);
	TSharedPtr<FNewNodeAction> NewQuestProgressNodeAction(
		new FNewNodeAction(
			UQuestProgressGraphNode::StaticClass(),
			FText::FromString(TEXT("Quests")),
			FText::FromString(TEXT("New Quest Progress Node")),
			FText::FromString(TEXT("Makes a new node that can give information about a quest. Use $total for the total number of items needed.\n Use $current for the current number of items collected.")),
			0)
			);
	
	ContextMenuBuilder.AddAction(NewDialogueNodeAction);
	ContextMenuBuilder.AddAction(NewEndNodeAction);
	ContextMenuBuilder.AddAction(NewCheckQuestNodeAction);
	ContextMenuBuilder.AddAction(NewCompleteQuestNodeAction);
	ContextMenuBuilder.AddAction(NewStartQuestNodeAction);
	ContextMenuBuilder.AddAction(NewQuestProgressNodeAction);
	ContextMenuBuilder.AddAction(NewRandomDialogueNodeAction);
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
