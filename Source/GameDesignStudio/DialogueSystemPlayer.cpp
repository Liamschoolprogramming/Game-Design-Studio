// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemPlayer.h"

#include "CompleteQuestNodeInfo.h"
#include "DialogueAsset.h"
#include "DialogueCheckQuestNodeInfo.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "DialogueResponseButtonController.h"
#include "Macros.h"
#include "QuestDialogueUIController.h"
#include "Components/Image.h"

#include "Components/VerticalBoxSlot.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/QuestManager.h"

DEFINE_LOG_CATEGORY_STATIC(DialoguePlayer, Log, All);

void UDialogueSystemPlayer::PlayDialogue(class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController,
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
UDialogueSpeakerComponent* UDialogueSystemPlayer::FindSpeakerComponent(UWorld* World, FName SpeakerName)
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

void UDialogueSystemPlayer::ChooseOptionAtIndex(int Index)
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
			DialogueWidget->CharacterName->SetText(FText::FromString(Speaker->SpeakerName.ToString()));
			if (Speaker->SpeakerImage)
			{
				DialogueWidget->CharacterPortrait->SetBrushFromTexture(Speaker->SpeakerImage);
			}
			CurrentSpeakerComponent = Speaker;
		}
		
	}
	else if (CurrentNode != nullptr && CurrentNode->NodeType == EDialogueNodeType::CheckQuestsNode)
	{
		if (const UDialogueCheckQuestNodeInfo* NodeInfo = Cast<UDialogueCheckQuestNodeInfo>(CurrentNode->NodeInfo))
		{
			if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
			{
				switch (QuestManager->GetQuestState(NodeInfo->QuestName))
				{
					case EQuestState::ACTIVE:
						ChooseOptionAtIndex(0);
					case EQuestState::INACTIVE:
						ChooseOptionAtIndex(1);
					case EQuestState::COMPLETED:
						ChooseOptionAtIndex(2);
					
				}

					
			}
			
		}
		
	}
	else if (CurrentNode != nullptr && CurrentNode->NodeType == EDialogueNodeType::CompleteQuestGraphNode)
	{
		if ( UCompleteQuestNodeInfo* NodeInfo = Cast<UCompleteQuestNodeInfo>(CurrentNode->NodeInfo))
		{
			if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
			{
				if (QuestManager->CompleteQuest(NodeInfo->QuestName))
				{
					ChooseOptionAtIndex(0);
				}
				else
				{
					ChooseOptionAtIndex(1);
				}
			}
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
