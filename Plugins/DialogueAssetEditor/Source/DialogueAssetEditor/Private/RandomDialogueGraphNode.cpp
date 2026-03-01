// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomDialogueGraphNode.h"

#include <string>


FText URandomDialogueGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UDialogueNodeInfo* DialogueNodeInfo = Cast<UDialogueNodeInfo>(NodeInfo);
	if (DialogueNodeInfo->Title.IsEmpty())
	{
		FString DialogueTextString = TEXT("Random Dialogue ");
		DialogueTextString = DialogueTextString + FString::FromInt((NodeInfo->DialogueOptions.Num())) + TEXT(" Options");
		
		
		
		return FText::FromString(DialogueTextString);
	}
	return DialogueNodeInfo->Title;
}

void URandomDialogueGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Response")),
		FText::FromString(TEXT("Creates a new response")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<URandomDialogueGraphNode*>(this),
			&URandomDialogueGraphNode::HandleAddPin
			)
			 
			
		)
	);
	
	section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Response")),
		FText::FromString(TEXT("Deletes the last response")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<URandomDialogueGraphNode*>(this),
			&URandomDialogueGraphNode::HandleDeletePin
			)
			 
			
		)
	);
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<URandomDialogueGraphNode*>(this),
			&URandomDialogueGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* URandomDialogueGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, TEXT("Display"));
}

void URandomDialogueGraphNode::CreateDefaultOutputPins()
{
	FString defaultResponse = TEXT("Continue");
	CreateDialoguePin(EGPD_Output, FName(defaultResponse));
	GetDialogueNodeInfo()->DialogueResponses.Add(FText::FromString(defaultResponse));
}

UEdGraphPin* URandomDialogueGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName SubCategory = TEXT("DialoguePin");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}

void URandomDialogueGraphNode::SyncPinsWithResponses()
{
	//Sync pins with data
	//first pin is the input
	UDialogueNodeInfo* DialogueNodeInfo = GetDialogueNodeInfo();
	int NumGraphNodePins = Pins.Num() - 1;
	int NumInfoPins = DialogueNodeInfo->DialogueResponses.Num();

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
			FName(DialogueNodeInfo->DialogueResponses[NumGraphNodePins].ToString())
			);
		NumGraphNodePins++;
	}
	
	//sync text
	int index = 1;
	for (const FText& option : DialogueNodeInfo->DialogueResponses)
	{
		GetPinAt(index)->PinName = FName(option.ToString());
		index++;
	}
}

void URandomDialogueGraphNode::HandleAddPin()
{
	GetDialogueNodeInfo()->DialogueResponses.Add(FText::FromString(TEXT("Response")));
	SyncPinsWithResponses();
	
	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void URandomDialogueGraphNode::HandleDeletePin()
{
	UEdGraphPin* Pin = GetPinAt(Pins.Num() - 1);
	if (Pin->Direction != EGPD_Input)
	{
		UDialogueNodeInfo* DialogueNodeInfo = GetDialogueNodeInfo();
		DialogueNodeInfo->DialogueResponses.RemoveAt(DialogueNodeInfo->DialogueResponses.Num() - 1);
		SyncPinsWithResponses();
		
		GetGraph()->NotifyGraphChanged();
		GetGraph()->Modify();
	}
	
}

void URandomDialogueGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
