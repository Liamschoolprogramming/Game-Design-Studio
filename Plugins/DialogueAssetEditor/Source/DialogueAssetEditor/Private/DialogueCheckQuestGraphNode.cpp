// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueCheckQuestGraphNode.h"

FText UDialogueCheckQuestGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	
	return FText::FromString(TEXT("Check Quest"));
}

void UDialogueCheckQuestGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UDialogueCheckQuestGraphNode*>(this),
			&UDialogueCheckQuestGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UDialogueCheckQuestGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UDialogueCheckQuestGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Active");
	FString defaultNegative = TEXT("Inactive");
	FString defaultComplete =  TEXT("Complete");
	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
	
	CreateDialoguePin(EGPD_Output, FName(defaultNegative));
	CreateDialoguePin(EGPD_Output, FName(defaultComplete));
	
}

UEdGraphPin* UDialogueCheckQuestGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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

void UDialogueCheckQuestGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
