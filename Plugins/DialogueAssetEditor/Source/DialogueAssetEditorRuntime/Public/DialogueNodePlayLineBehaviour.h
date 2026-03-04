#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"

#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "DialogueNodePlayLineBehaviour.generated.h"

UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialoguePlayLineBehaviour : public UDialogueNodeBehaviour
{
GENERATED_BODY()

public:

virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
{
    UDialogueNodeInfo* NodeInfo = Cast<UDialogueNodeInfo>(NodeInfoBase);
    if(!NodeInfo) return;
    
    Handler->SetDialogueText(NodeInfo->DialogueText);
    Handler->ClearResponses();
    
    int OptionIndex = 0;
    for (FText Response : NodeInfo->DialogueResponses)
    {
        Handler->AddResponseButton(Response, OptionIndex);
        OptionIndex++;
    }
    Handler->SetupCameraAndSpeaker(NodeInfo->CameraName, NodeInfo->SpeakerName, NodeInfo->CharacterPortrait);
}

};