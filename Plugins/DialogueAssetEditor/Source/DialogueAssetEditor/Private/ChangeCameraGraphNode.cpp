// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeCameraGraphNode.h"
#include "DialogueGraphNodeFactory.h"
//Autoregister self


REGISTER_DIALOGUE_NODE(
	"ChangeCameraGraphNode",
	UChangeCameraGraphNode,
	"Camera",
	"New Change Camera Node",
	"Makes a new node that plays a camera animation before moving on.",
	0,
	true
);
NODE_TITLE(UChangeCameraGraphNode, "Change Camera", CameraName);
GET_CONTEXT_ACTION(UChangeCameraGraphNode);
CREATE_PINS(UChangeCameraGraphNode,"Camera", "On Complete");
