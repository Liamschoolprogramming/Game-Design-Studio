#pragma once
#include "DialogueGraphNodeBase.h"

using FNodeFactoryFunc = TFunction<UDialogueGraphNodeBase*(UObject* Outer)>;

class FDialogueGraphNodeFactory
{
public:
	static void RegisterNodeType(FName NodeType, FNodeFactoryFunc Factory)
	{
		GetRegistry().Add(NodeType, Factory);
	}
	static UDialogueGraphNodeBase* CreateNode(FName NodeType, UObject* Outer)
	{
		if (FNodeFactoryFunc* Factory = GetRegistry().Find(NodeType))
		{
			return (*Factory)(Outer);
		}
		return nullptr;
	}

	static TMap<FName, FNodeFactoryFunc>& GetRegistry()
	{
		static TMap<FName, FNodeFactoryFunc> Registry;
		return Registry;
	}
};