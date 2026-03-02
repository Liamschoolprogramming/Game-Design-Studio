// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeCameraGraphNode.h"
#include "DialogueGraphNodeFactory.h"
//Autoregister self


REGISTER_DIALOGUE_NODE(
	"ChangeCameraGraphNode",
	UChangeCameraGraphNode,
	"Camera",
	"New Change Camera Node",
	"Makes a new node that plays a camera animation before moving on.",
	0,
	true
);

FText UChangeCameraGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr)
	{
		FString OutputString = TEXT("Change Camera");
		if (!NodeInfo->CameraName.IsNone())
		{
			FString ActionData = NodeInfo->CameraName.ToString();
			if (ActionData.Len() > 15)
			{
				ActionData = ActionData.Left(15) + TEXT("...");
			}
			OutputString += TEXT(" - ") + ActionData;
		}
		return FText::FromString(OutputString);
	}
	return FText::FromString(TEXT("Change Camera"));
}

void UChangeCameraGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UChangeCameraGraphNode*>(this),
			&UChangeCameraGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UChangeCameraGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UChangeCameraGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("On Complete");
	
	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
}

UEdGraphPin* UChangeCameraGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName SubCategory = TEXT("Camera");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}

void UChangeCameraGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
