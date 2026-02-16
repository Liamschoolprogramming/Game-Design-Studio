#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "DialogueGraphSchema.generated.h"

UCLASS()
class UDialogueGraphSchema:public UEdGraphSchema
{
	GENERATED_BODY()
	
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
};

USTRUCT()
struct FNewNodeAction: public FEdGraphSchemaAction
{
GENERATED_BODY()
	
	public:
	FNewNodeAction(){}
	FNewNodeAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, uint32 InGroupingIndex)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGroupingIndex) {}
	
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,const FVector2f& Location, bool bSelectNewNode = true) override;
};