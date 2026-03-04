#pragma once

#include "DialogueGraphNodeBase.h"
#include "EdGraph/EdGraphNode.h"
#include "StartGraphNode.generated.h"

UCLASS()
class UStartGraphNode : public UDialogueGraphNodeBase
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
