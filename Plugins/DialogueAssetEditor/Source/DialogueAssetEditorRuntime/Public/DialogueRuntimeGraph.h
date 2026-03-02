#pragma once


#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueNodeBehaviour.h"
#include "UObject/NameTypes.h"
#include "DialogueRuntimeGraph.generated.h"



UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API  UDialogueeRuntimePin: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PinName;
	
	UPROPERTY()
	FGuid PinId;
	
	UPROPERTY()
	UDialogueeRuntimePin* Connection = nullptr;
	
	UPROPERTY()
	class UDialogueRuntimeNode* Parent = nullptr;
};

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API  UDialogueRuntimeNode: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName NodeType = "DialogueNode";
	
	UPROPERTY()
	UDialogueeRuntimePin* InputPin;
	
	UPROPERTY()
	TArray<UDialogueeRuntimePin*> OutputPins;
	
	UPROPERTY()
	UDialogueNodeBehaviour* NodeBehaviour = nullptr;
	
	UPROPERTY()
	FVector2D Position;
	
	UPROPERTY()
	UDialogueNodeInfoBase* NodeInfo = nullptr;
};

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API  UDialogueRuntimeGraph: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<UDialogueRuntimeNode*> Nodes;
};