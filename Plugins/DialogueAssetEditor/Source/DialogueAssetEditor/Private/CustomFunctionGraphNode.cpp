// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFunctionGraphNode.h"
#include "DialogueGraphNodeFactory.h"

//Autoregister self
REGISTER_DIALOGUE_NODE(
	"CustomFunctionGraphNode",
	UCustomFunctionGraphNode,
	"Tools",
	"New Custom Function Node",
	"Makes a new node that calls the given function, if implemented.",
	0,
	true
);
FText UCustomFunctionGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr)
	{
		FString OutputString = TEXT("Call Function");
		if (!NodeInfo->FunctionName.IsEmpty())
		{
			FString ActionData = NodeInfo->FunctionName;
			if (ActionData.Len() > 15)
			{
				ActionData = ActionData.Left(15) + TEXT("...");
			}
			OutputString += TEXT(" - ") + ActionData;
		}
		return FText::FromString(OutputString);
	}
	return FText::FromString(TEXT("Call Function"));
}

void UCustomFunctionGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UCustomFunctionGraphNode*>(this),
			&UCustomFunctionGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UCustomFunctionGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UCustomFunctionGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Completed");
	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
}

UEdGraphPin* UCustomFunctionGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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

void UCustomFunctionGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
