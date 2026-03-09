// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFunctionGraphNode.h"

#include "DialogueGraphNode.h"
#include "DialogueGraphNodeFactory.h"
REGISTER_DIALOGUE_NODE(
	"CustomFunctionGraphNode",
	UCustomFunctionGraphNode,
	"Tools",
	"New Custom Function Node",
	"Makes a new node that calls the given function, if implemented.",
	0,
	true
);
NODE_TITLE(UCustomFunctionGraphNode, "Change Camera", FunctionName);
GET_CONTEXT_ACTION(UCustomFunctionGraphNode);
CREATE_PINS(UCustomFunctionGraphNode,"Camera", "On Complete");
