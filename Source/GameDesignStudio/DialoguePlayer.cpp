// Fill out your copyright notice in the Description page of Project Settings.


#include "DialoguePlayer.h"

#include "DialogueAsset.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Runtime/CookOnTheFly/Internal/CookOnTheFly.h"
#include "DialogueResponseButtonController.h"
#include "QuestDialogueUIController.h"
#include "ToolBuilderUtil.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

DEFINE_LOG_CATEGORY_STATIC(DialoguePlayer, Log, All);

void UDialoguePlayer::PlayDialogue(class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController,
                                    FOnDialogueEnded InOnDialogueEnded)
{
	OnDialogueEnded = InOnDialogueEnded;
	UDialogueRuntimeGraph* RuntimeGraph = InDialogueAsset->Graph;
	
	//get start node
	for (UDialogueRuntimeNode* Node : RuntimeGraph->Nodes)
	{
		if (Node->NodeType == EDialogueNodeType::StartNode)
		{
			CurrentNode = Node;
			break;
		}
	}
	if (CurrentNode == nullptr)
	{
		UE_LOG(DialoguePlayer, Error, TEXT("No start node"));
		return;
	}
	//create and display dialogue UI
	DialogueWidget = UQuestDialogueUIController::CreateInstance(InPlayerController);
	DialogueWidget->AddToViewport();
	
	ChooseOptionAtIndex(0);
}
UDialogueSpeakerComponent* UDialoguePlayer::FindSpeakerComponent(UWorld* World, FName SpeakerName)
{
	if (!World) return nullptr;
	if (SpeakerName == NAME_None) return nullptr;
	
	//some goofy search
	for (TObjectIterator<UDialogueSpeakerComponent> It; It; ++It)
	{
		if (It->GetWorld() != World)
			continue;

		if (It->ComponentHasTag(SpeakerName))
		{
			return *It;
		}
	}

	return nullptr;
}

void UDialoguePlayer::ChooseOptionAtIndex(int Index)
{
	if (Index >= CurrentNode->OutputPins.Num() || Index < 0)
	{
		UE_LOG(DialoguePlayer, Error, TEXT("Invalid response option at index %d"), Index);	
		return ;
	}
	
	UDialogueeRuntimePin* OutputPin = CurrentNode->OutputPins[Index];
	if (OutputPin->Connection != nullptr)
	{
		CurrentNode = OutputPin->Connection->Parent;
	}
	else
	{
		//no connection so we assume it's an end node
		CurrentNode = nullptr;
	}
	if (CurrentNode != nullptr && CurrentNode->NodeType == EDialogueNodeType::DialogueNode)
	{
		UDialogueNodeInfo* NodeInfo = Cast<UDialogueNodeInfo>(CurrentNode->NodeInfo);
		//set the DialogueText named Text object on the widget
		DialogueWidget->DialogueText->SetText(NodeInfo->DialogueText);
		
		DialogueWidget->ResponseBox->ClearChildren();
		int OptionIndex = 0;
		for (FText response : NodeInfo->DialogueResponses)
		{
			UDialogueResponseButtonController* Button = UDialogueResponseButtonController::CreateInstance(DialogueWidget->GetOwningPlayer());
			Button->SetClickHandler(OptionIndex, [this](int OptionIndex)
			{
				ChooseOptionAtIndex(OptionIndex);
			});
			Button->ResponseButtonText->SetText(response);
			UVerticalBoxSlot* Slot = DialogueWidget->ResponseBox->AddChildToVerticalBox(Button);
			Slot->SetPadding(FMargin(10));
			
			OptionIndex++;
		}
		if (UDialogueSpeakerComponent* Speaker = FindSpeakerComponent(GetWorld(), NodeInfo->SpeakerName))
		{
			Speaker->ActivateSpeakerCamera();
		}
		
	} 
	else if (CurrentNode == nullptr || CurrentNode->NodeType == EDialogueNodeType::EndNode)
	{
		APlayerController* PlayerController = DialogueWidget->GetOwningPlayer();
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
		
		EDialogueNodeAction Action = EDialogueNodeAction::None;
		FString ActionData = TEXT("");
		if (CurrentNode != nullptr)
		{
			UDialogueEndNodeInfo* EndNodeInfo = Cast<UDialogueEndNodeInfo>(CurrentNode->NodeInfo);
			Action = EndNodeInfo->Action;
			ActionData = EndNodeInfo->ActionData;
		}
		OnDialogueEnded.ExecuteIfBound(Action, ActionData);
	}
}
