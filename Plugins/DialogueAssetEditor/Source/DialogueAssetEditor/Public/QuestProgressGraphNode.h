// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "QuestProgressNodeInfo.h"
#include "QuestProgressGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UQuestProgressGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public: //UEdGraph interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor(1.f, 0.631f, 0.f));
	}

	virtual bool CanUserDeleteNode() const override { return true; }

	virtual void
	GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;


	virtual EDialogueNodeType GetDialogueNodeType() const override
	{
		return EDialogueNodeType::QuestProgressGraphNode;
	}

	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;


	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UQuestProgressNodeInfo>(Owner);
	}

	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UQuestProgressNodeInfo>(InNodeInfo);
	}

	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}

	virtual UQuestProgressNodeInfo* GetDialogueNodeInfo()
	{
		return NodeInfo;
	}

protected:
	UPROPERTY()
	class UQuestProgressNodeInfo* NodeInfo = nullptr;

private:
	void HandleDeleteNode();
};
