// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueCheckQuestNode.h"

FText UDialogueCheckQuestNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UDialogueCheckQuestNodeInfo* DialogueNodeInfo = Cast<UDialogueCheckQuestNodeInfo>(NodeInfo);
	if (DialogueNodeInfo->Title.IsEmpty())
	{
		FString DialogueTextString = DialogueNodeInfo->DialogueText.ToString();
		if (DialogueTextString.Len() > 15)
		{
			DialogueTextString = DialogueTextString.Left(15) + TEXT("...");
		}
		return FText::FromString(DialogueTextString);
	}
	return DialogueNodeInfo->Title;
}

void UDialogueCheckQuestNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);
}

UEdGraphPin* UDialogueCheckQuestNode::CreateDefaultInputPin()
{
	return Super::CreateDefaultInputPin();
}

void UDialogueCheckQuestNode::CreateDefaultOutputPins()
{
	Super::CreateDefaultOutputPins();
}

UEdGraphPin* UDialogueCheckQuestNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	return Super::CreateDialoguePin(Direction, Name);
}

void UDialogueCheckQuestNode::SyncPinsWithResponses()
{
}

void UDialogueCheckQuestNode::HandleAddPin()
{
}

void UDialogueCheckQuestNode::HandleDeletePin()
{
}

void UDialogueCheckQuestNode::HandleDeleteNode()
{
}
