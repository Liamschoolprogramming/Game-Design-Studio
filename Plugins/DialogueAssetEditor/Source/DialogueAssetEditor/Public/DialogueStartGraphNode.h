#pragma once

#include "DialogueGraphNodeBase.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueStartGraphNode.generated.h"

UCLASS()
class UDialogueStartGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public: // UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override {return FText::FromString("Start");};
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor::Red);
	}
	virtual bool CanUserDeleteNode() const override{ return false; }

	  
	
public://our interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	
	virtual FName GetDialogueNodeType() const override
	{
		return "StartNode";
	}
};
