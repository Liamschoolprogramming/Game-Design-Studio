// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestProgressGraphNode.h"


#include "DialogueGraphNodeFactory.h"
//Autoregister self
namespace
{
	struct FAutoRegisterDialogueNode
	{
		FAutoRegisterDialogueNode()
		{
			FDialogueGraphNodeFactory::RegisterNode(
			{
				"QuestProgressGraphNode",
				UQuestProgressGraphNode::StaticClass(),
				FText::FromString(TEXT("Quests")),
			FText::FromString(TEXT("New Quest Progress Node")),
			FText::FromString(TEXT("Makes a new node that can give information about a quest. Use $total for the total number of items needed.\n Use $current for the current number of items collected.")),
				0
			});
		}
	};

	static FAutoRegisterDialogueNode AutoRegister;
}

FText UQuestProgressGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr)
	{
		FString OutputString = TEXT("Check Quest Progress");
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
	return FText::FromString(TEXT("Check Quest Progress"));
}

void UQuestProgressGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UQuestProgressGraphNode*>(this),
			&UQuestProgressGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UQuestProgressGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));
}

void UQuestProgressGraphNode::CreateDefaultOutputPins()
{
	FString defaultPositive = TEXT("Continue");

	CreateDialoguePin(EGPD_Output, FName(defaultPositive));
}

UEdGraphPin* UQuestProgressGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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

void UQuestProgressGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
