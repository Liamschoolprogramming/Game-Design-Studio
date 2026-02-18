#include "DialogueStartGraphNode.h"

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
