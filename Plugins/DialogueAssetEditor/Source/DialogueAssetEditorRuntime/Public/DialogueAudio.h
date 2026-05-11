#pragma once

#include "CoreMinimal.h"
#include "DialogueAudio.generated.h"

USTRUCT(Blueprintable)
struct FDialogueAudio
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> Audio = nullptr;
	UPROPERTY(EditAnywhere)
	bool bPerWord = false;
};
