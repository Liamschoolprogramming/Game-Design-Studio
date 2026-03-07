// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFunctionParamGraphNode.h"

REGISTER_DIALOGUE_NODE(
	"CustomFunctionParamNode",
	UCustomFunctionParamGraphNode,
	"Tools",
	"New Custom Function with Parameters",
	"Creates a new custom function node that can pass along parameter arguments.",
	0,
	true)

NODE_TITLE(UCustomFunctionParamGraphNode,"Custom Function", Parameters.Name)
GET_CONTEXT_ACTION(UCustomFunctionParamGraphNode)
CREATE_PINS(UCustomFunctionParamGraphNode, "Tools", "Continue")