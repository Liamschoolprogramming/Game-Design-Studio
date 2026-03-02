#include "StartGraphNode.h"


#include "DialogueGraphNodeFactory.h"
//Autoregister self
REGISTER_DIALOGUE_NODE(
	"StartNode",
	UStartGraphNode,
	"",
	"",
	"",
	0,
	false
);

UEdGraphPin* UStartGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
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
