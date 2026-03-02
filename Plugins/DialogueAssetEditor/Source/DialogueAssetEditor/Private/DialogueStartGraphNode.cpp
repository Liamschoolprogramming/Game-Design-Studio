#include "DialogueStartGraphNode.h"


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
				"StartNode",
				UDialogueStartGraphNode::StaticClass(),
				FText::GetEmpty(),
				FText::GetEmpty(),
				FText::GetEmpty(),
				0,
				false
				
			});
		}
	};

	static FAutoRegisterDialogueNode AutoRegister;
}

UEdGraphPin* UDialogueStartGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Output");
	FName SubCategory = TEXT("StartPin");
	
	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name);
	Pin->PinType.PinSubCategory = SubCategory;
	
	return Pin;
}
