#include "DialogueEndGraphNode.h"

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
				"EndNode",
				UDialogueEndGraphNode::StaticClass(),
				FText::FromString(TEXT("Control Nodes")),
			FText::FromString(TEXT("New End Node")),
			FText::FromString(TEXT("Makes a new end node")),
				0
			});
		}
	};

	static FAutoRegisterDialogueNode AutoRegister;
}



FText UDialogueEndGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
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


void UDialogueEndGraphNode::HandleDeleteNode()
{
	GetGraph()->RemoveNode(this);
		
	GetGraph()->NotifyGraphChanged();
	GetGraph()->Modify();
}

void UDialogueEndGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu,
                                                      class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("End Node Actions")));
	
	section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateUObject(
			const_cast<UDialogueEndGraphNode*>(this),
			&UDialogueEndGraphNode::HandleDeleteNode
			)
			 
			
		)
	);
}

UEdGraphPin* UDialogueEndGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Inputs");
	FName Subcategory = TEXT("EndPin");
	
	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = Subcategory;
	
	return Pin;
}

UEdGraphPin* UDialogueEndGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EGPD_Input, FName(TEXT("Finish")));
}

