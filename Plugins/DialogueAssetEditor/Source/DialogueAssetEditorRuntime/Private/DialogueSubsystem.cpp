// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSubsystem.h"
#include "DialogueSave.h"
#include "DialogueAsset.h"
#include "Kismet/GameplayStatics.h"

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("Dialogue Subsystem Initialized"));
	
	// Iterate all loaded UClasses
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
	 
		// Skip abstract, interface classes, or those not derived from UObject
		if (Class->HasAnyClassFlags(CLASS_Abstract | CLASS_Interface) ||
			!Class->IsChildOf(UObject::StaticClass()))
		{
			continue;
		}
	 
		// Check if this class implements your plugin interface
		if (Class->ImplementsInterface(UDialogueExecutionHandler::StaticClass()))
		{
			// Instantiate instance owned by this subsystem
			UObject* Instance = NewObject<UObject>(this, Class);
			if (Instance)
			{
				AutoCreatedInstances.Add(Instance);
				UE_LOG(LogTemp, Log, TEXT("Instantiated class: %s"), *Class->GetName());
			}
		}
	}
	
}

void UDialogueSubsystem::Deinitialize()
{
	UnregisterAllStateData();
	AutoCreatedInstances.Empty();
	Super::Deinitialize();
}

TMap<FSoftObjectPath, FStateData> UDialogueSubsystem::GetStateDataMap() const
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
	
	FSoftObjectPath Key = Tree.ToSoftObjectPath();
	UE_LOG(LogTemp, Warning, TEXT("Registering State Data"));
	if (!Tree.IsNull())
	{
		
		DialogueTreeStates.Add(Key, StateData);
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
	FSoftObjectPath Key = Tree.ToSoftObjectPath();
	if (!Tree.IsNull())
	{
		DialogueTreeStates.Remove(Key);
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
	SaveDialogue();
}


TArray<TScriptInterface<class IDialogueExecutionHandler>> UDialogueSubsystem::GetDialogueDelegates()	
{
	TArray<TScriptInterface<class IDialogueExecutionHandler>> Delegates;
	for (const auto& Instance : AutoCreatedInstances)
	{
		UObject* ObjectInstance = Cast<UObject>(Instance);
		if (ObjectInstance && ObjectInstance->Implements<UDialogueExecutionHandler>())
		{
			TScriptInterface<IDialogueExecutionHandler> Interface(ObjectInstance);
			Delegates.Add(Interface);
		}
	}
	return Delegates;
}

void UDialogueSubsystem::StartDialogue(UDialogueAsset* InDialogueAsset, AActor* InOwner, APlayerController* InPlayerController)
{
	
	if (!DialogueAsset && !InDialogueAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Asset selected"));
		return;
	}
	if (InDialogueAsset)
	{
		DialogueAsset = InDialogueAsset;
	}

	
	//DialoguePlayer->OnCustomFunctionParam.AddUFunction(this,"CustomFunctionParam");
	
	for (UObject* Instance : AutoCreatedInstances)
	{
		if (IDialogueExecutionHandler* InterfacePtr = Cast<IDialogueExecutionHandler>(Instance))
		{
			InterfacePtr->PlayDialogue(InOwner, InDialogueAsset, InPlayerController);
		}
	}

}

void UDialogueSubsystem::SaveDialogue()
{

	if (!DialogueSave)
	{
		if (UGameplayStatics::DoesSaveGameExist(TEXT("DialogueSave"), 0))
		{
			DialogueSave = Cast<UDialogueSave>(
				UGameplayStatics::LoadGameFromSlot(TEXT("DialogueSave"), 0)
			);
		}
		else
		{
			DialogueSave = Cast<UDialogueSave>(
				UGameplayStatics::CreateSaveGameObject(UDialogueSave::StaticClass())
			);
		}
	}
	
	for (const auto& State : DialogueTreeStates)
	{
		DialogueSave->SavedDialogueTreeStates.Add(State.Key,State.Value);
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