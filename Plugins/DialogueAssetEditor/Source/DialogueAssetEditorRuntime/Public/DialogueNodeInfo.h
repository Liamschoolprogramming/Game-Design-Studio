#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfo.generated.h"

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueNodeInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Title;
	
	UPROPERTY(EditAnywhere)
	FText DialogueText;
	
	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueResponses;
};
