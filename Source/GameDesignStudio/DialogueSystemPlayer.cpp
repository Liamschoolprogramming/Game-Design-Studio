// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemPlayer.h"

#include "QuestNodeInfo.h"
#include "DialogueAsset.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "DialogueResponseButtonController.h"
#include "Macros.h"
#include "PlayerControllerBase.h"
#include "QuestDialogueUIController.h"
#include "QuestProgressNodeInfo.h"
#include "RandomDialogueNodeInfo.h"
#include "Components/Image.h"

#include "Components/VerticalBoxSlot.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Managers/QuestManager.h"

DEFINE_LOG_CATEGORY_STATIC(DialoguePlayerSub, Log, All);

UDialogueSystemPlayer::UDialogueSystemPlayer()
{
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(
		TEXT("/Game/GameDesignStudio/Dialogue/TestCharacterPortraits/T_DefaultCharacterPortrait.T_DefaultCharacterPortrait")
	);
	if (TextureObj.Succeeded())
	{
		DefaultCharacterIcon = TextureObj.Object;
	}
}

void UDialogueSystemPlayer::PlayDialogue(class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController,
                                         FOnDialogueEnded InOnDialogueEnded)
{
	PlayerController = Cast<APlayerControllerBase>(InPlayerController);
	
	PlayerController->SetCanMove(false);
	OnDialogueEnded = InOnDialogueEnded;
	UDialogueRuntimeGraph* RuntimeGraph = InDialogueAsset->Graph;
	
	//get start node
	for (UDialogueRuntimeNode* Node : RuntimeGraph->Nodes)
	{
		if (Node->NodeType == "StartNode")
		{
			CurrentNode = Node;
			break;
		}
	}
	if (CurrentNode == nullptr)
	{
		UE_LOG(DialoguePlayerSub, Error, TEXT("No start node"));
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

ADialogueCineCamera* UDialogueSystemPlayer::FindCineCamera(UWorld* World, FName InCameraName)
{
	if (!World) return nullptr;
	if (InCameraName == NAME_None) return nullptr;
	
	for (TObjectIterator<ADialogueCineCamera> It; It; ++It)
	{
		if (It->GetWorld() != World)
			continue;
		if (It->CameraName == InCameraName)
		{
			return *It;
		}
	}
	return nullptr;
}

void UDialogueSystemPlayer::SetDialogueText(FText InText)
{
	if (DialogueWidget)
	{
		DialogueWidget->DialogueText->SetText(InText);
	}
}

void UDialogueSystemPlayer::ClearResponses()
{
	if (DialogueWidget)
	{
		DialogueWidget->ResponseBox->ClearChildren();
	}
}

void UDialogueSystemPlayer::AddResponseButton(FText InResponseText, int InOptionIndex)
{
	UDialogueResponseButtonController* Button = UDialogueResponseButtonController::CreateInstance(DialogueWidget->GetOwningPlayer());
	Button->SetClickHandler(InOptionIndex, [this](int Index){ ChooseOptionAtIndex(Index); });
	Button->ResponseButtonText->SetText(InResponseText);
	UVerticalBoxSlot* Slot = DialogueWidget->ResponseBox->AddChildToVerticalBox(Button);
	Slot->SetPadding(FMargin(10));
}

void UDialogueSystemPlayer::SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, UTexture2D* Portrait)
{
	ADialogueCineCamera* Camera = FindCineCamera(GetWorld(), CameraName);
	UDialogueSpeakerComponent* Speaker = FindSpeakerComponent(GetWorld(), InSpeakerName);

	if (Camera && Speaker)
	{
		Camera->ActivateCamera();
		DialogueWidget->CharacterName->SetText(FText::FromString(InSpeakerName.ToString()));
		Speaker->SpeakerImage = Portrait ? Portrait : DefaultCharacterIcon;
		DialogueWidget->CharacterPortrait->SetBrushFromTexture(Speaker->SpeakerImage);
		CurrentSpeakerComponent = Speaker;
	}
	else if (Speaker)
	{
		Speaker->ActivateSpeakerCamera();
		DialogueWidget->CharacterName->SetText(FText::FromString(InSpeakerName.ToString()));
		Speaker->SpeakerImage = Portrait ? Portrait : DefaultCharacterIcon;
		DialogueWidget->CharacterPortrait->SetBrushFromTexture(Speaker->SpeakerImage);
		CurrentSpeakerComponent = Speaker;
	}
}

void UDialogueSystemPlayer::EndDialogue(EDialogueNodeAction Action, FString ActionData)
{
	DialogueWidget->RemoveFromParent();
	DialogueWidget = nullptr;
	if (PlayerController)
	{
		PlayerController->SetCanMove(true);
		if (CurrentSpeakerComponent)
		{
			PlayerController->SetViewTargetWithBlend(PlayerController->PlayerReference,CurrentSpeakerComponent->CameraTransitionTime);
		}
		else
		{
			PlayerController->SetViewTargetWithBlend(PlayerController->PlayerReference,.5f);
		}
		
	}
	CurrentSpeakerComponent = nullptr;
	OnDialogueEnded.ExecuteIfBound(Action, ActionData);
}

TArray<int> UDialogueSystemPlayer::GetQuestProgress(FName QuestKey)
{
	if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
	{
		
			return QuestManager->GetQuestProgress(QuestKey);
	}			
	return {-1, -1};
}

void UDialogueSystemPlayer::StartQuest(FName QuestKey)
{
	
	if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
	{
		QuestManager->ActivateQuestForItem(QuestKey);
		ChooseOptionAtIndex(0);
	}

}

void UDialogueSystemPlayer::CompleteQuest(FName QuestKey)
{
	if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
	{
		if (QuestManager->CompleteQuest(QuestKey))
		{
			ChooseOptionAtIndex(0);
		}
		else
		{
			ChooseOptionAtIndex(1);
		}
	}
}

void UDialogueSystemPlayer::CheckQuest(FName QuestKey)
{
	if (UQuestManager* QuestManager = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetQuestManager())
	{
		switch (QuestManager->GetQuestState(QuestKey))
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

void UDialogueSystemPlayer::ChooseOptionAtIndex(int Index)
{
	if (Index >= CurrentNode->OutputPins.Num() || Index < 0)
	{
		UE_LOG(DialoguePlayerSub, Error, TEXT("Invalid response option at index %d"), Index);	
		return ;
	}

	if (UDialogueeRuntimePin* OutputPin = CurrentNode->OutputPins[Index]; OutputPin->Connection != nullptr)
	{
		CurrentNode = OutputPin->Connection->Parent;
	}
	else
	{
		//no connection so we assume it's an end node
		CurrentNode = nullptr;
	}
	if (CurrentNode != nullptr)
	{
		if (CurrentNode->NodeBehaviour)
		{
			CurrentNode->NodeBehaviour->Execute(CurrentNode->NodeInfo, this);
		}
		else
		{
			UE_LOG(DialoguePlayerSub, Error, TEXT("Current Node %s has no behaviour"), *CurrentNode->NodeType.ToString())
		}
	}
	else if (CurrentNode == nullptr)
	{
		EndDialogue(EDialogueNodeAction::None, "");
		
		Debug::PrintToScreen("No end node but no further connection, closing the dialogue.", FColor::Red);
	}
}
