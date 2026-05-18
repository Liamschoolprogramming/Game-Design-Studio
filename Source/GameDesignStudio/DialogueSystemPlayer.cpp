// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemPlayer.h"

#include "QuestNodeInfo.h"
#include "DialogueAsset.h"
#include "DialogueNodeInfo.h"
#include "DialogueRuntimeGraph.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DialogueSubsystem.h"
#include "DialogueResponseButtonController.h"
#include "Macros.h"
#include "PlayerControllerBase.h"
#include "QuestDialogueUIController.h"
#include "QuestProgressNodeInfo.h"
#include "RandomDialogueNodeInfo.h"
#include "StateBranchNodeInfo.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/Image.h"

#include "Components/VerticalBoxSlot.h"
#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
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

void UDialogueSystemPlayer::PlayDialogue(class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController)
{
	if (!bCanStartDialogue) return;
	if (!InDialogueAsset)
	{
		UE_LOG(DialoguePlayerSub, Error, TEXT("PlayDialogue called with null asset"));
		return;
	}

	UDialogueRuntimeGraph* RuntimeGraph = InDialogueAsset->Graph;
	if (!RuntimeGraph || RuntimeGraph->Nodes.IsEmpty())
	{
		UE_LOG(DialoguePlayerSub, Error, 
			TEXT("RuntimeGraph is null or empty for asset: %s. Was it compiled?"), 
			*InDialogueAsset->GetName());
		return;
	}
	bCanStartDialogue = false;
	PlayerController = Cast<APlayerControllerBase>(InPlayerController);
	
	PlayerController->SetCanMove(false);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController,nullptr);
	PlayerController->SetShowMouseCursor(true);
	DialogueAsset = InDialogueAsset;
	
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
		UE_LOG(DialoguePlayerSub, Error, TEXT("No start node in graph. How did you do this?"));
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

		UE_LOG(LogTemp, Display, TEXT("FindSpeakerComponent %s"), *It->SpeakerName.ToString());

		if (It->SpeakerName == SpeakerName)
		{
			return *It;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("No speaker found with name %s, make sure you set it in the node properties and the speaker component"), *SpeakerName.ToString());
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
	UE_LOG(LogTemp, Error, TEXT("No Camera found with name %s, make sure you set it in the node properties and the speaker component"), *InCameraName.ToString());
	return nullptr;
}

void UDialogueSystemPlayer::CooldownEnded()
{
	bCanStartDialogue = true;
}

void UDialogueSystemPlayer::ChooseFirstOptionAndEnableDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
	
	ChooseOptionAtIndex(0);
}

void UDialogueSystemPlayer::RevealNextWord()
{
	if (!TextArray.IsValidIndex(CurrentWordIndex))
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
		bIsPlaying = false;
		return;
	}

	// Append a space between words
	if (CurrentWordIndex > 0)
	{
		DialogueText.Append(TEXT(" "));
	}

	if (bPlayAudioPerWord)
	{
		LoadAndPlayDialogueSound();
	}
	
	DialogueText.Append(TextArray[CurrentWordIndex]);
	CurrentWordIndex++;

	if (DialogueWidget)
	{
		DialogueWidget->DialogueText->SetText(FText::FromString(DialogueText));
	}
		

	// Schedule next word with slight random variance
	float Variance = FMath::RandRange(-DialogueSpeedVariance, DialogueSpeedVariance);
	float NextDelay = FMath::Max(0.05f, DialogueSpeed + Variance);
    
	GetWorld()->GetTimerManager().SetTimer(
		DialogueTimerHandle,
		this,
		&UDialogueSystemPlayer::RevealNextWord,
		NextDelay,
		false // not looping, reschedule each word
	);
}
void UDialogueSystemPlayer::RevealAllWords()
{
	GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
	bIsPlaying = false;
	DialogueText.Empty();
	CurrentWordIndex = 0;
	for (auto Line : TextArray)
	{
		if (CurrentWordIndex > 0)
		{
			DialogueText.Append(TEXT(" "));
		}
		DialogueText.Append(Line);
		CurrentWordIndex++;
	}
	if (DialogueWidget)
	{
		DialogueWidget->DialogueText->SetText(FText::FromString(DialogueText));
	}
}

void UDialogueSystemPlayer::SetDialogueText(FText InText, float TextSpeed, float SpeedVariance)
{
	FString EditText = InText.ToString();
	EditText.ParseIntoArray(TextArray,TEXT(" "),true);
	
	DialogueSpeed = 1/TextSpeed;
	if (DialogueWidget)
	{
		DialogueWidget->DialogueText->SetText(FText::FromString(TEXT("")));
	}
	DialogueSpeedVariance = SpeedVariance;
	
	CurrentWordIndex = 0;
	DialogueText.Empty();
	if (!bPlayAudioPerWord)
	{
		LoadAndPlayDialogueSound();
	}

	bIsPlaying = true;
	GetWorld()->GetTimerManager().SetTimer(
		DialogueTimerHandle,
		this,
		&UDialogueSystemPlayer::RevealNextWord,
		DialogueSpeed,
		false // looping
	);
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

void UDialogueSystemPlayer::SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, const TSoftObjectPtr<UObject> Portrait)
{
	ADialogueCineCamera* Camera = FindCineCamera(GetWorld(), CameraName);
	UDialogueSpeakerComponent* Speaker = FindSpeakerComponent(GetWorld(), InSpeakerName);

	if (!Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("No Camera"))
	}
	if (!Speaker)
	{
		UE_LOG(LogTemp, Error, TEXT("No Speaker"))
	}
	
	
	if (Camera && Speaker)
	{
		UObject* Asset = Portrait.LoadSynchronous();

		if (UTexture2D* AsTexture = Cast<UTexture2D>(Asset))
		{
			
			DialogueWidget->CharacterPortrait->SetBrushFromTexture(AsTexture);
		}
		else if (UMaterialInterface* AsMaterial = Cast<UMaterialInterface>(Asset))
		{
			DialogueWidget->CharacterPortrait->SetBrushFromMaterial(AsMaterial);
		}
		else
		{
			DialogueWidget->CharacterPortrait->SetBrushFromTexture(DefaultCharacterIcon);
		}
		Camera->ActivateCamera();
		DialogueWidget->CharacterName->SetText(FText::FromString(InSpeakerName.ToString()));
		
		CurrentSpeakerComponent = Speaker;
	}
	else if (Speaker)
	{
		Speaker->ActivateSpeakerCamera();
		DialogueWidget->CharacterName->SetText(FText::FromString(InSpeakerName.ToString()));
		UObject* Asset = Portrait.LoadSynchronous();
		
		if (UTexture2D* AsTexture = Cast<UTexture2D>(Asset))
		{
			DialogueWidget->CharacterPortrait->SetBrushFromTexture(AsTexture);
		}
		else if (UMaterialInterface* AsMaterial = Cast<UMaterialInterface>(Asset))
		{
			DialogueWidget->CharacterPortrait->SetBrushFromMaterial(AsMaterial);
		}
		else
		{
			DialogueWidget->CharacterPortrait->SetBrushFromTexture(DefaultCharacterIcon);
		}
		CurrentSpeakerComponent = Speaker;
	}
}

void UDialogueSystemPlayer::EndDialogue()
{
	if (CurrentDialogueAudio != nullptr)
	{
		CurrentDialogueAudio->Stop();
		CurrentDialogueAudio = nullptr;
	}
	DialogueWidget->RemoveFromParent();
	DialogueWidget->Destruct();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "CooldownEnded");
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DialogueCooldown, false);
	DialogueWidget = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("DialogueSystemPlayer::EndDialogue"));
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Found"));
		PlayerController->SetCanMove(true);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
		
		if (CurrentSpeakerComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrentSpeakerComponent Found, switching to %s"), *PlayerController->PlayerReference->GetName());
			
			PlayerController->SetViewTargetWithBlend(PlayerController->CameraReference,CurrentSpeakerComponent->CameraTransitionTime);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Speaker component Not Found"));
			PlayerController->SetViewTargetWithBlend(PlayerController->CameraReference,.5f);
		}
		
	}
	CurrentSpeakerComponent = nullptr;
	UDialogueSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	if (Subsystem)
	{
		Subsystem->OnDialogueEnded.Broadcast(EDialogueNodeAction::None, "");
		Subsystem->bInDialogue = false;
	}
	
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

void UDialogueSystemPlayer::ChangeCamera(FName CameraName, float TransitionTime, bool bReenableDialogueAfterAnimation)
{
	UE_LOG(LogTemp, Display, TEXT("Finding Camera"));
	if (ADialogueCineCamera* Camera = FindCineCamera(GetWorld(),CameraName))
	{
		PlayerController->SetViewTargetWithBlend(Camera, TransitionTime);
		OnCameraChange.Broadcast();
		Camera->ActivateCamera();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
		if (bReenableDialogueAfterAnimation)
		{
			UE_LOG(LogTemp, Display, TEXT("ChooseFirstOption and enable dialogue"));
			Camera->OnFinishAnimation.AddUObject(this, &UDialogueSystemPlayer::ChooseFirstOptionAndEnableDialogue);
		}
		else
		{
			Camera->OnFinishAnimation.AddUObject(this, &UDialogueSystemPlayer::ChooseFirstOption);
		}
		
	}else
	{
		ChooseOptionAtIndex(0);
	}
}

UObject* UDialogueSystemPlayer::GetCurrentNode()
{
	return CurrentNode;
}

void UDialogueSystemPlayer::CallCustomFunction(FString FunctionName)
{
	UDialogueSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	Subsystem->OnDialogueEnded.Broadcast(EDialogueNodeAction::BPFunction, FunctionName);
	ChooseOptionAtIndex(0);
}

UDialogueAsset* UDialogueSystemPlayer::GetAsset()
{
	UE_LOG(LogTemp, Display, TEXT("GetAsset"));
	return DialogueAsset;
}

void UDialogueSystemPlayer::ChooseOption(int IndexToChoose)
{
	ChooseOptionAtIndex(IndexToChoose);
}

UWorld* UDialogueSystemPlayer::GetWorldFromPlayer()
{
	return GetWorld();
}

void UDialogueSystemPlayer::CheckDialogueState()
{
	UStateBranchNodeInfo* NodeInfo = Cast<UStateBranchNodeInfo>(CurrentNode->NodeInfo);
	if (!NodeInfo) return;
	UDialogueSubsystem* DialogueSubsystem =  GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	if (DialogueSubsystem->GetStateDataByTree(DialogueAsset).first)
	{
		FStateData Data = DialogueSubsystem->GetStateDataByTree(DialogueAsset).second;
		if (Data.State == EStates::NotStarted)
		{
			UE_LOG(LogTemp, Display, TEXT("Dialogue is not started"));
			ChooseOptionAtIndex(0);
		}
		else if (Data.State == EStates::Finished)
		{
			UE_LOG(LogTemp, Display, TEXT("Dialogue is completed"));
			ChooseOptionAtIndex(1);
		}
		else if (Data.State == EStates::FinishedWithTag)
		{
			UE_LOG(LogTemp, Display, TEXT("Dialogue is completed with tag"));
			int index = 2;
			bool bFoundtag =false;
			for (FText Option : NodeInfo->EditableStatesResponses)
			{
				FString Text = Option.ToString();
				UE_LOG(DialoguePlayerSub, Error, TEXT("Checking %s against %s"), *Option.ToString(), *Data.Tag)
				if (Text.Equals(Data.Tag))
				{
					bFoundtag = true;
					ChooseOptionAtIndex(index);
				}
				index++;
			}
			if (!bFoundtag)
			{
				UE_LOG(DialoguePlayerSub, Error, TEXT("Cannot find the tag %s"),*Data.Tag);
				ChooseOptionAtIndex(0);
			}
			
		}
	}
	else
	{
		UE_LOG(DialoguePlayerSub, Error, TEXT("Could not load pointer"));
		ChooseOptionAtIndex(0);
	}
}

void UDialogueSystemPlayer::PlayDialogue(AActor* InOwner, class UDialogueAsset* InDialogueAsset, APlayerController* InPlayerController)
{
	Owner = InOwner;
	PlayDialogue(InDialogueAsset, InPlayerController);
}


void UDialogueSystemPlayer::SetUpPlayAudioPerWord(USoundBase* AudioToPlay)
{
	if (AudioToPlay)
	{
		DialogueSound = AudioToPlay;
		
	}
	else
	{
		DialogueSound = nullptr;
	}
}

void UDialogueSystemPlayer::LoadAndPlayDialogueSound()
{
	if (DialogueSound != nullptr)
	{
		// Stop previous line if still playing
		if (CurrentDialogueAudio != nullptr)
		{
			CurrentDialogueAudio->Stop();
			CurrentDialogueAudio = nullptr;
		}

		DialogueSound->ConditionalPostLoad();
		CurrentDialogueAudio = UGameplayStatics::SpawnSound2D(GetWorld(), DialogueSound);
	}
}

void UDialogueSystemPlayer::PlayAudio(FDialogueAudio AudioIn)
{
	
	bPlayAudioPerWord = AudioIn.bPerWord;
	
	if (!AudioIn.Audio.IsNull())
	{
		DialogueSound = AudioIn.Audio.LoadSynchronous();
	}
	else
	{
		DialogueSound = nullptr;
	}
	
	
}

void UDialogueSystemPlayer::SkipLine(int32 Index, bool bContinueToNextLine)
{
	if (bIsPlaying)
	{
		RevealAllWords();
	}
	else if (bContinueToNextLine)
	{
		ChooseOptionAtIndex(Index);
	}
}

/*
void UDialogueSystemPlayer::CallCustomFunctionWithParams(FString FunctionName, const FDialogueParameters& Parameters)
{
	
	OnCustomFunctionParam.Broadcast(FunctionName, Parameters);
	ChooseOptionAtIndex(0);
}*/


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
		EndDialogue();
		UE_LOG(DialoguePlayerSub, Warning, TEXT("No end node but no further connection, closing the dialogue."))
		
	}
}
