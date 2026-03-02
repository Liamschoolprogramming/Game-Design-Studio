#include "EndGraphNode.h"

#include "DialogueGraphNodeFactory.h"
//Autoregister self
REGISTER_DIALOGUE_NODE(
	"EndNode",
	UEndGraphNode,
	"Control Nodes",
	"New End Node",
	"Makes a new end node. It can run a function on end if needed.",
	0,
	true
);




FText UEndGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr && NodeInfo->Action != EDialogueNodeAction::None)
	{
		FString OutputString = UEnum::GetDisplayValueAsText(NodeInfo->Action).ToString();
		if (!NodeInfo->ActionData.IsEmpty())
		{
			FString ActionData = NodeInfo->ActionData;
			if (ActionData.Len() > 15)
			{
				ActionData = ActionData.Left(15) + TEXT("...");
			}
			OutputString += TEXT(" - ") + ActionData;
		}
		return FText::FromString(OutputString);
	}
	return FText::FromString(TEXT("End"));
}


void UEndGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
		
	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void UEndGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
                                                      class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("End Node Actions")));
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UEndGraphNode*>(this),
			&UEndGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UEndGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Inputs");
	FName Subcategory = TEXT("EndPin");
	
	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = Subcategory;
	
	return Pin;
}

UEdGraphPin* UEndGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, FName(TEXT("Finish")));
}

