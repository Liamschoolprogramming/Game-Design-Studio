// Fill out your copyright notice in the Description page of Project Settings.


#include "StateSwitchGraphNode.h"

REGISTER_DIALOGUE_NODE(
	"StateSwitchNode",
	UStateSwitchGraphNode,
	"Tools",
	"New State Switch Node",
	"Makes a new node that switches based on the subsystem.",
	0,
	true
);
NODE_TITLE(UStateSwitchGraphNode, "State Switch", EditableStatesResponses.Num())
GET_CONTEXT_ACTION_MULTI(UStateSwitchGraphNode, UStateBranchNodeInfo, EditableStatesResponses)


void UStateSwitchGraphNode::SyncPinsWithResponses()
{
	//Sync pins with data
	//first pin is the input
	TArray<FText> Outputs;
	Outputs.Add(FText::FromString("Not Started"));
	Outputs.Add(FText::FromString("Finished"));
	for (const FText& Output : NodeInfo->EditableStatesResponses)
	{
		Outputs.Add(Output);
	}
	int NumGraphNodePins = Pins.Num() - 1;
	int NumInfoPins = Outputs.Num();

	//match pin counts
	while (NumGraphNodePins > NumInfoPins){}
	{
		RemovePinAt(NumGraphNodePins - 1, EGPD_Output);
		NumGraphNodePins--;
	}
	while (NumInfoPins > NumGraphNodePins)
	{
		CreateDialoguePin(
			EGPD_Output,
			FName(Outputs[NumGraphNodePins].ToString())
			);
		NumGraphNodePins++;
	}
	
	//sync text
	int index = 1;
	for (const FText& option : Outputs)
	{
		GetPinAt(index)->PinName = FName(option.ToString());
		index++;
	}
}


UEdGraphPin* UStateSwitchGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UStateSwitchGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Not Started");
	FString defaultNegative = TEXT("Finished");
	
	
	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
	CreateDialoguePin(EGPD_Output, FName(defaultNegative));

	for ( FText PinName : NodeInfo->EditableStatesResponses)
	{
		CreateDialoguePin(EGPD_Output, FName( PinName.ToString()));
	}
}

UEdGraphPin* UStateSwitchGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName SubCategory = TEXT("Tools");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}