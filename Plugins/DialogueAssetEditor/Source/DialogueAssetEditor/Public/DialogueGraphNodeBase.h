#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeType.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueGraphNodeBase.generated.h"

UCLASS()
class UDialogueGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public: // our interface
	
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
	{
		
		/* Override for functionality */
		return nullptr;
	}
	virtual UEdGraphPin* CreateDefaultInputPin()
	{
		return nullptr;
	}
	virtual void CreateDefaultOutputPins()
	{
		/* Override for functionality */
	}
	
	virtual void InitNodeInfo(UObject* Owner)
	{
		/* Override for functionality */
	}
	virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo)
	{
		/* Override for functionality */
	}
	virtual UDialogueNodeInfoBase* GetNodeInfo() const
	{
		/* Override for functionality */
		return nullptr;
	}
	
	virtual EDialogueNodeType GetDialogueNodeType() const
	{
		return EDialogueNodeType::Unknown;
	}
	
	virtual void OnPropertiesChanged()
	{
		/* Override for functionality */
	}
	
};
