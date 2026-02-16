#include "CustomGraphSchema.h"

#include "CustomGraphNode.h"

void UCustomGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewNodeAction(
		new FNewNodeAction(
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Node")),
			FText::FromString(TEXT("Makes a new node")),
			0)
			);
	
	ContextMenuBuilder.AddAction(NewNodeAction);
}

const FPinConnectionResponse UCustomGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
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

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,const FVector2f& Location, bool bSelectNewNode)
{
	UCustomGraphNode* Result = NewObject<UCustomGraphNode>(ParentGraph);
	Result->CreateNewGuid();
	
	Result->NodePosX = Location.X;
	Result->NodePosY = Location.Y;
	
	UEdGraphPin* InputPin = Result->CreateCustomPin(EGPD_Input,TEXT("SomeInput"));
	
	Result->CreateCustomPin(EGPD_Output,TEXT("SomeOutput1"));
	Result->CreateCustomPin(EGPD_Output,TEXT("SomeOutput2"));
	
	if (FromPin != nullptr)
	{
		Result->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}
	
	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);
	
	
	return Result;
	
}
