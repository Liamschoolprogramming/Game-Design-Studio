#pragma once

#include "DialogueGraphNodeBase.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeInfo.h"
#include "DialogueGraphNode.generated.h"

UCLASS()
class UDialogueGraphNode : public UDialogueGraphNodeBase
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
	
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;
	
	
	
	virtual EDialogueNodeType GetDialogueNodeType() const override
	{
		return EDialogueNodeType::DialogueNode;
	}
	
	virtual void OnPropertiesChanged() override
	{
		SyncPinsWithResponses();
	}
	
	
public: //Dialogue interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	void SyncPinsWithResponses();
	
	
	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UDialogueNodeInfo>(Owner);
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UDialogueNodeInfo>(InNodeInfo);
	}
	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}
	virtual UDialogueNodeInfo* GetDialogueNodeInfo()
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
