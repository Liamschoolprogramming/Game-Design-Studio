// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSubsystem.h"
#include "DialogueSave.h"
#include "DialogueAsset.h"
#include "Kismet/GameplayStatics.h"

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Subsystem Initialized"));
	
	
	
}

void UDialogueSubsystem::Deinitialize()
{
	UnregisterAllStateData();
	Super::Deinitialize();
}

TMap<TSoftObjectPtr<UDialogueAsset>, FStateData> UDialogueSubsystem::GetStateDataMap() const
{
	return DialogueTreeStates;
}

std::pair<bool, FStateData> UDialogueSubsystem::GetStateDataByTree(UDialogueAsset* Tree) const
{
	if (Tree)
	{
		if (DialogueTreeStates.Contains(Tree))
		{
			return std::make_pair(true, DialogueTreeStates[Tree]);
		}
		else
		{
			return std::make_pair(false, FStateData());
		}
	}
	else
	{
		return std::make_pair(false, FStateData());
	}
}

bool UDialogueSubsystem::RegisterStateData(const TSoftObjectPtr<UDialogueAsset>& Tree, const FStateData& StateData)
{
	UE_LOG(LogTemp, Warning, TEXT("Registering State Data"));
	if (Tree.IsValid())
	{
		
		if (DialogueTreeStates.Contains(Tree))
		{
			DialogueTreeStates.Remove(Tree);
			DialogueTreeStates.Add(Tree, StateData);
		}
		else
		{
			DialogueTreeStates.Add(Tree, StateData);
		}
		UE_LOG(LogTemp, Warning, TEXT("Registered State Data"));
		SaveDialogue();
		return true;
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Tree"));
		return false;
	}
}

bool UDialogueSubsystem::UnregisterStateData(TSoftObjectPtr<UDialogueAsset> Tree)
{
	if (Tree.IsValid())
	{
		DialogueTreeStates.Remove(Tree);
		return true;
	}
	else
	{
		return false;
	}
}

void UDialogueSubsystem::UnregisterAllStateData()
{
	DialogueTreeStates.Empty();
}
void UDialogueSubsystem::SaveDialogue()
{
	if (DialogueSave)
	{
		DialogueSave->SavedDialogueTreeStates = DialogueTreeStates;
	}
	else
	{
		DialogueSave = NewObject<UDialogueSave>();
		DialogueSave->SavedDialogueTreeStates = DialogueTreeStates;
	}
	for (const auto& State : DialogueTreeStates)
	{
		FStateData StateData = State.Value;
		UE_LOG(LogTemp, Warning, TEXT("%hhd State, %s Tag"), StateData.State, *StateData.Tag);
	}
	UE_LOG(LogTemp, Warning, TEXT("Should see data above"));
	UE_LOG(LogTemp, Warning, TEXT("Saved Dialogue Tree"));
	UGameplayStatics::SaveGameToSlot(DialogueSave,FString(TEXT("DialogueSave")), 0);
}

void UDialogueSubsystem::LoadDialogue()
{
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("DialogueSave")), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded Save"));
		DialogueSave = Cast<UDialogueSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("DialogueSave")), 0));
		DialogueTreeStates = DialogueSave->SavedDialogueTreeStates;

		for (const auto& State : DialogueTreeStates)
		{
			FStateData StateData = State.Value;
			UE_LOG(LogTemp, Warning, TEXT("%hhd State, %s Tag"), StateData.State, *StateData.Tag);
		}
		UE_LOG(LogTemp, Warning, TEXT("Should see data above"));
		
	}
}