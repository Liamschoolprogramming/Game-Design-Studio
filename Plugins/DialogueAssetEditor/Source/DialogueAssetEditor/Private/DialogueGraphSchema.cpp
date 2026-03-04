#include "DialogueGraphSchema.h"

#include "CompleteQuestGraphNode.h"
#include "CheckQuestGraphNode.h"
#include "EndGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueGraphNodeFactory.h"
#include "StartGraphNode.h"
#include "DialogueNodeInfo.h"
#include "QuestProgressGraphNode.h"
#include "RandomDialogueGraphNode.h"
#include "StartQuestGraphNode.h"

//this defines actions on nodes

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	
	for (const FDialogueNodeRegistration& Node : FDialogueGraphNodeFactory::GetAllNodes())
	{
		if (!Node.bShowInContextMenu)
		{
			continue;
		}
		TSharedPtr<FNewNodeAction> NewNodeAction =
			MakeShared<FNewNodeAction>(
				Node.GraphNodeClass,
				Node.Category,
				Node.MenuName,
				Node.Tooltip,
				Node.Priority
			);

		ContextMenuBuilder.AddAction(NewNodeAction);
	}
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
	UStartGraphNode* StartNode = NewObject<UStartGraphNode>(&Graph);
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
	Result->InitNodeBehaviour(Result);
	
	
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
