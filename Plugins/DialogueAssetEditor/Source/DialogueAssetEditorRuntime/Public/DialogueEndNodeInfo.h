#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueSharedTypes.h"
#include "DialogueEndNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueEndNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere)
	EStates EndState;

	UPROPERTY(EditAnywhere)
	FString EndStateTag = TEXT("");
	
};