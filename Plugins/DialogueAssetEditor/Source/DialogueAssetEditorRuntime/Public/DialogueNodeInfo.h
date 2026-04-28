#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueSpeakerComponent.h"
#include "DialogueNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Title;
	
	UPROPERTY(EditAnywhere, Category="DialogueText")
	FText DialogueText;
	
	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueResponses;
	
	UPROPERTY(EditAnywhere)
	FName SpeakerName;
	
	UPROPERTY(EditAnywhere)
	//Leave empty to use SpeakerName for the camera
	FName CameraName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta =(AllowedClasses = "/Script/Engine.Texture2D,/Script/Engine.MaterialInterface", DisplayThumbnail = "true"))
	TSoftObjectPtr<UObject> CharacterPortrait = nullptr;
	
};
