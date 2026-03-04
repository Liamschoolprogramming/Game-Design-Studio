#pragma once

#pragma once

#include "DialogueEndNodeInfo.h"
#include "EdGraph/EdGraphNode.h"
#include "EndNodeBehaviour.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueGraphNodeBase.h"
#include "EndGraphNode.generated.h"


UCLASS()
class UEndGraphNode : public UDialogueGraphNodeBase
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
	
	virtual void InitNodeBehaviour(UObject* Owner) override
	{
		NodeBehaviour = NewObject<UEndNodeBehaviour>(Owner);
	}
	
	virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override
	{
		NodeBehaviour = Cast<UEndNodeBehaviour>(InNodeInfo);
	}
	
	virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override
	{
		return NodeBehaviour;
	}
protected:
	UPROPERTY()
	class UEndNodeBehaviour* NodeBehaviour = nullptr;
	
protected:
	UPROPERTY()
	class UDialogueEndNodeInfo* NodeInfo = nullptr;
	
};
