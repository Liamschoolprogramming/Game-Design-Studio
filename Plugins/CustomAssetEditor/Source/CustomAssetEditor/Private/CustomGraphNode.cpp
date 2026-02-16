#include "CustomGraphNode.h"

#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"



void UCustomGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
                                                 class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Custom Node Actions")));
	
	section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"),TEXT("CustomAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UCustomGraphNode*>(this),
			&UCustomGraphNode::HandleAddPin
			)
			 
			
		)
	);
	
	section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Pin")),
		FText::FromString(TEXT("Deletes the last pin")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"),TEXT("CustomAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UCustomGraphNode*>(this),
			&UCustomGraphNode::HandleDeletePin
			)
			 
			
		)
	);
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("CustomAssetEditorStyle"),TEXT("CustomAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UCustomGraphNode*>(this),
			&UCustomGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
	
}

UEdGraphPin* UCustomGraphNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");
	FName SubCategory = TEXT("CustomPin");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}

void UCustomGraphNode::HandleAddPin()
{
	CreateCustomPin(EGPD_Output,TEXT("AnotherOutput"));
				
	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void UCustomGraphNode::HandleDeletePin()
{
	UEdGraphPin* Pin = GetPinAt(Pins.Num() - 1);
	if (Pin->Direction != EGPD_Input)
	{
		RemovePin(Pin);
		
		GetGraph()->NotifyGraphChanged();
		GetGraph()->Modify();
	}
	
	
}

void UCustomGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
}
