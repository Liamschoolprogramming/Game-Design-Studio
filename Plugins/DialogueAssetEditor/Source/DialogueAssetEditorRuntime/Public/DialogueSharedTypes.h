#pragma once

#include "CoreMinimal.h"
#include "DialogueSharedTypes.generated.h"

UENUM(BlueprintType)
enum class EStates : uint8
{
	NotStarted,
	Finished,
	FinishedWithTag
};

UENUM(BlueprintType)
enum class EDialogueNodeAction : uint8
{
	None,
	StartQuest,
	BPFunction
};

USTRUCT()
struct FStateData
{
	GENERATED_BODY()

	UPROPERTY()
	EStates State;
	UPROPERTY()
	FString Tag;
};

