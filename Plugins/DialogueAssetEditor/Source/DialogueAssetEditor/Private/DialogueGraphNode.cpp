#include "DialogueGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"



void UDialogueGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
                                                 class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));
	
	section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a pin")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UDialogueGraphNode*>(this),
			&UDialogueGraphNode::HandleAddPin
			)
			 
			
		)
	);
	
	section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Pin")),
		FText::FromString(TEXT("Deletes the last pin")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UDialogueGraphNode*>(this),
			&UDialogueGraphNode::HandleDeletePin
			)
			 
			
		)
	);
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UDialogueGraphNode*>(this),
			&UDialogueGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
	
}

UEdGraphPin* UDialogueGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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

void UDialogueGraphNode::HandleAddPin()
{
	CreateDialoguePin(EGPD_Output,TEXT("AnotherOutput"));
				
	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void UDialogueGraphNode::HandleDeletePin()
{
	UEdGraphPin* Pin = GetPinAt(Pins.Num() - 1);
	if (Pin->Direction != EGPD_Input)
	{
		RemovePin(Pin);
		
		GetGraph()->NotifyGraphChanged();
		GetGraph()->Modify();
	}
	
	
}

void UDialogueGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
