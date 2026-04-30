#pragma once

#include "DialogueGraphNodeBase.h"
#include "StartNodeBehaviour.h"
#include "StartNodeInfo.h"
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

	
	
	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UStartNodeInfo>(Owner);
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UStartNodeInfo>(InNodeInfo);
	}
	virtual UStartNodeInfo* GetNodeInfo() const override
	{
		return NodeInfo;
	}
	
	virtual FName GetDialogueNodeType() const override
	{
		return "StartNode";
	}
	
	virtual void OnPropertiesChanged() override
	{
		Modify();
	}
	
	virtual void InitNodeBehaviour(UObject* Owner) override
	{
		NodeBehaviour = NewObject<UStartNodeBehaviour>(Owner);
	}
	
	virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override
	{
		NodeBehaviour = Cast<UStartNodeBehaviour>(InNodeInfo);
	}
	
	virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override
	{
		return NodeBehaviour;
	}
protected:
	UPROPERTY()
	class UStartNodeBehaviour* NodeBehaviour = nullptr;
	
protected:
	UPROPERTY()
	class UStartNodeInfo* NodeInfo = nullptr;
	
};
