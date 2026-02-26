// Fill out your copyright notice in the Description page of Project Settings.


#include "StartQuestGraphNode.h"

FText UStartQuestGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr)
	{
		FString OutputString = TEXT("Start Quest");
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
	return FText::FromString(TEXT("Start Quest"));
}

void UStartQuestGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UStartQuestGraphNode*>(this),
			&UStartQuestGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UStartQuestGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UStartQuestGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Started");

	CreateDialoguePin(EGPD_Output, FName(defaultPositive));

}

UEdGraphPin* UStartQuestGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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

void UStartQuestGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
