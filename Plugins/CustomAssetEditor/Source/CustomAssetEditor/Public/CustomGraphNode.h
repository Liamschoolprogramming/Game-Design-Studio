#pragma once

#include "EdGraph/EdGraphNode.h"
#include "CustomGraphNode.generated.h"

UCLASS()
class UCustomGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return FText::FromString(TEXT("MyNodeTitle"));
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor::Green);
	}
	virtual bool CanUserDeleteNode() const override{ return true; }

	UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name);

	
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	
private:
	void HandleAddPin();
	void HandleDeletePin();
	void HandleDeleteNode();
};
