// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionNodeBehaviour.h"
#include "CustomFunctionNodeInfo.h"
#include "DialogueGraphNodeBase.h"

#include "CustomFunctionGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UCustomFunctionGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public: //UEdGraph interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor::Blue);
	}

	virtual bool CanUserDeleteNode() const override { return true; }

	virtual void
	GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;


	virtual FName GetDialogueNodeType() const override
	{
		return "CustomFunctionGraphNode";
	}

public: //Dialogue interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;


	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UCustomFunctionNodeInfo>(Owner);
	}

	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UCustomFunctionNodeInfo>(InNodeInfo);
	}

	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}

	virtual UCustomFunctionNodeInfo* GetDialogueNodeInfo()
	{
		return NodeInfo;
	}

	virtual void InitNodeBehaviour(UObject* Owner) override
	{
		NodeBehaviour = NewObject<UCustomFunctionNodeBehaviour>(Owner);
	}

	virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override
	{
		NodeBehaviour = Cast<UCustomFunctionNodeBehaviour>(InNodeInfo);
	}

	virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override
	{
		return NodeBehaviour;
	}

protected:
	UPROPERTY()
	class UCustomFunctionNodeBehaviour* NodeBehaviour = nullptr;

protected:
	UPROPERTY()
	class UCustomFunctionNodeInfo* NodeInfo = nullptr;

private:
	void HandleDeleteNode();
	//add other interfaces
};
