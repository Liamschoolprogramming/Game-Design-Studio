// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeCameraBehaviour.h"
#include "ChangeCameraNodeInfo.h"
#include "DialogueGraphNodeBase.h"

#include "ChangeCameraGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITOR_API UChangeCameraGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public: //UEdGraph interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor(FLinearColor(0.651, 0, 1));
	}

	virtual bool CanUserDeleteNode() const override { return true; }

	virtual void
	GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;


	virtual FName GetDialogueNodeType() const override
	{
		return "ChangeCameraGraphNode";
	}

public: //Dialogue interface
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;


	virtual void InitNodeInfo(UObject* Owner) override
	{
		NodeInfo = NewObject<UChangeCameraNodeInfo>(Owner);
	}

	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override
	{
		NodeInfo = Cast<UChangeCameraNodeInfo>(InNodeInfo);
	}

	virtual UDialogueNodeInfoBase* GetNodeInfo() const override
	{
		return NodeInfo;
	}

	virtual UChangeCameraNodeInfo* GetDialogueNodeInfo()
	{
		return NodeInfo;
	}

	virtual void InitNodeBehaviour(UObject* Owner) override
	{
		NodeBehaviour = NewObject<UChangeCameraBehaviour>(Owner);
	}

	virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override
	{
		NodeBehaviour = Cast<UChangeCameraBehaviour>(InNodeInfo);
	}

	virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override
	{
		return NodeBehaviour;
	}

protected:
	UPROPERTY()
	class UChangeCameraBehaviour* NodeBehaviour = nullptr;

protected:
	UPROPERTY()
	class UChangeCameraNodeInfo* NodeInfo = nullptr;

private:
	void HandleDeleteNode();
	//add other interfaces
};
