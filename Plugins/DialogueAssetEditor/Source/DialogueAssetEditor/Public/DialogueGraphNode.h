#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode.generated.h"

UCLASS()
class UDialogueGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public: //UEdGraph interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor::Green);
	}
	virtual bool CanUserDeleteNode() const override{ return true; }

	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	
	
public: //Dialogue interface
	UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name);
	void SyncPinsWithResponses();
	
	void SetNodeInfo(class UDialogueNodeInfo* InNodeInfo)
	{
		NodeInfo = InNodeInfo;
	}
	class UDialogueNodeInfo* GetNodeInfo()
	{
		return NodeInfo;
	}
	
protected:
	UPROPERTY()
	class UDialogueNodeInfo* NodeInfo = nullptr;
	
private:
	void HandleAddPin();
	void HandleDeletePin();
	void HandleDeleteNode();
};
