#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueSubsystem.h"
#include "DialogueEndNodeInfo.generated.h"

UENUM(BlueprintType)
enum class EDialogueNodeAction : uint8
{
	None,
	StartQuest, //ActionData is the QuestID
	BPFunction, //ActionData is passed into a bp switch
};

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueEndNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EDialogueNodeAction Action = EDialogueNodeAction::None;
	
	UPROPERTY(EditAnywhere)
	FString ActionData = TEXT("");

	UPROPERTY(EditAnywhere)
	EStates EndState = EStates::Finished;

	UPROPERTY(EditAnywhere)
	FString EndStateTag = TEXT("");
	
};