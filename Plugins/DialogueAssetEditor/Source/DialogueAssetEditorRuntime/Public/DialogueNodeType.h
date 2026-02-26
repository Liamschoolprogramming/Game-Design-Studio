#pragma once

#include "DialogueNodeType.generated.h"

UENUM()
enum class EDialogueNodeType
{
	Unknown,
	StartNode,
	DialogueNode,
	EndNode,
	CheckQuestsNode,
	CompleteQuestGraphNode,
	StartQuestGraphNode,
};