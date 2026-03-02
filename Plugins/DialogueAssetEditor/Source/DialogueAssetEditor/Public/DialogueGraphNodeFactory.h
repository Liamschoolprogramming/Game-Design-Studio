#pragma once
#include "DialogueGraphNodeBase.h"

struct FDialogueNodeRegistration
{
	FName NodeType;
	TSubclassOf<UDialogueGraphNodeBase> GraphNodeClass;

	FText Category;
	FText MenuName;
	FText Tooltip;
	int32 Priority;
	bool bShowInContextMenu = true;
};

using FNodeFactoryFunc = TFunction<UDialogueGraphNodeBase*(UObject* Outer)>;

class FDialogueGraphNodeFactory
{
public:
	static void RegisterNode(const FDialogueNodeRegistration& Registration)
	{
		GetRegistry().Add(Registration);
	}

	static UDialogueGraphNodeBase* CreateNode(
	FName NodeType,
	UObject* Outer)
	{
		for (const FDialogueNodeRegistration& Node : GetAllNodes())
		{
			if (Node.NodeType == NodeType)
			{
				return NewObject<UDialogueGraphNodeBase>(
					Outer,
					Node.GraphNodeClass
				);
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Unknown NodeType: %s"), *NodeType.ToString());
		return nullptr;
	}
	static const TArray<FDialogueNodeRegistration>& GetAllNodes()
	{
		return GetRegistry();
	}

private:
	static TArray<FDialogueNodeRegistration>& GetRegistry()
	{
		static TArray<FDialogueNodeRegistration> Registry;
		return Registry;
	}
};