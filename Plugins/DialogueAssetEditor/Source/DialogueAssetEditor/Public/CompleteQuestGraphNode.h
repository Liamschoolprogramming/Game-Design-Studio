// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompleteQuestBehaviour.h"
#include "QuestNodeInfo.h"
#include "DialogueGraphNodeBase.h"
#include "UObject/Object.h"
#include "CompleteQuestGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class UCompleteQuestGraphNode : public UDialogueGraphNodeBase
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


	virtual FName GetDialogueNodeType() const override
	{
		return "CompleteQuestGraphNode";
	}
		
public: //Dialogue interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;

	
	
	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UQuestNodeInfo>(Owner);
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UQuestNodeInfo>(InNodeInfo);
	}
	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}
	virtual UQuestNodeInfo* GetDialogueNodeInfo()
	{
		return NodeInfo;
	}
	
	virtual void InitNodeBehaviour(UObject* Owner) override
	{
		NodeBehaviour = NewObject<UCompleteQuestBehaviour>(Owner);
	}
	
	virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override
	{
		NodeBehaviour = Cast<UCompleteQuestBehaviour>(InNodeInfo);
	}
	
	virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override
	{
		return NodeBehaviour;
	}
	
protected:
	UPROPERTY()
	class UQuestNodeInfo* NodeInfo = nullptr;
	UPROPERTY()
	class UCompleteQuestBehaviour* NodeBehaviour = nullptr;
	
private:
	void HandleDeleteNode();
};
