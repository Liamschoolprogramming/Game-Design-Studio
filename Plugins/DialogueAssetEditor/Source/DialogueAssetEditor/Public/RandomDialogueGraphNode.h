// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode.h"
#include "UObject/Object.h"
#include "RandomDialogueNodeInfo.h"
#include "RandomDialogueGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API URandomDialogueGraphNode : public UDialogueGraphNodeBase
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
	
	
	
	virtual FName GetDialogueNodeType() const override
	{
		return "RandomDialogueNode";
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
		NodeInfo = NewObject<URandomDialogueNodeInfo>(Owner);
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<URandomDialogueNodeInfo>(InNodeInfo);
	}
	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}
	virtual URandomDialogueNodeInfo* GetDialogueNodeInfo()
	{
		return NodeInfo;
	}
protected:
	UPROPERTY()
	class URandomDialogueNodeInfo* NodeInfo = nullptr;
private:
	void HandleAddPin();
	void HandleDeletePin();
	void HandleDeleteNode();
};

