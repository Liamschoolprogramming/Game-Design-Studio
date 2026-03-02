// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckQuestGraphNode.h"
#include "DialogueGraphNodeFactory.h"

//Autoregister self
REGISTER_DIALOGUE_NODE(
	"CheckQuestsNode",
	UCheckQuestGraphNode,
	"Quests",
	"New Check Quest Node",
	"Makes a new node that checks the status of a given quest.",
	0,
	true
);


FText UCheckQuestGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	
	if (NodeInfo != nullptr)
	{
		FString OutputString = TEXT("Check Quest");
		if (!NodeInfo->QuestName.IsNone())
		{
			FString ActionData = NodeInfo->QuestName.ToString();
			if (ActionData.Len() > 15)
			{
				ActionData = ActionData.Left(15) + TEXT("...");
			}
			OutputString += TEXT(" - ") + ActionData;
		}
		return FText::FromString(OutputString);
	}
	return FText::FromString(TEXT("Complete Quest"));
}

void UCheckQuestGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UCheckQuestGraphNode*>(this),
			&UCheckQuestGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UCheckQuestGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UCheckQuestGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Active");
	FString defaultNegative = TEXT("Inactive");
	FString defaultComplete =  TEXT("Complete");
	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
	
	CreateDialoguePin(EGPD_Output, FName(defaultNegative));
	CreateDialoguePin(EGPD_Output, FName(defaultComplete));
	
}

UEdGraphPin* UCheckQuestGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName SubCategory = TEXT("Quest");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}

void UCheckQuestGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
