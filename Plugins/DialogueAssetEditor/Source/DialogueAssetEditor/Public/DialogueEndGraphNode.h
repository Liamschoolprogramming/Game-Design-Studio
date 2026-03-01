#pragma once

#pragma once

#include "DialogueEndNodeInfo.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeType.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueEndGraphNode.generated.h"


UCLASS()
class UDialogueEndGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
	
public: //UEdGraphNode
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor::Blue);
	}
	virtual bool CanUserDeleteNode() const override{ return true; }


	void HandleDeleteNode();
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public: // UDialogueGraphNodeBase
	
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	
	
	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UDialogueEndNodeInfo>(Owner);
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UDialogueEndNodeInfo>(InNodeInfo);
	}
	virtual UDialogueEndNodeInfo* GetNodeInfo() const override
	{
		return NodeInfo;
	}
	
	virtual FName GetDialogueNodeType() const override
	{
		return "EndNode";
	}
	
	virtual void OnPropertiesChanged() override
	{
		Modify();
	}
	
protected:
	UPROPERTY()
	class UDialogueEndNodeInfo* NodeInfo = nullptr;
	
};
