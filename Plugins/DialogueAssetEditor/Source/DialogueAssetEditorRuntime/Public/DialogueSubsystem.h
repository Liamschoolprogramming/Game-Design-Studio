// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSharedTypes.h"
#include "InstancedStruct.h"
#include "DialogueSubsystem.generated.h"


class FOnDialogueEnded;
class UDialogueAsset;
class UDialogueSave;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueEnded, EDialogueNodeAction, DialogueNodeActionParam, const FString&, StringParam);


/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	TMap<FSoftObjectPath, FStateData> GetStateDataMap() const;

	std::pair<bool,FStateData> GetStateDataByTree(UDialogueAsset* Tree) const; 

	bool RegisterStateData(const TSoftObjectPtr<UDialogueAsset>& Tree, const FStateData& StateData);
	bool UnregisterStateData(TSoftObjectPtr<UDialogueAsset> Tree);

	UPROPERTY()
	UDialogueSave* DialogueSave = nullptr;
	
	UPROPERTY()
	UDialogueAsset* DialogueAsset = nullptr;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnded OnDialogueEnded;
	
	UPROPERTY()
	TArray<UObject*> AutoCreatedInstances;
	
	UFUNCTION(BlueprintCallable)
	TArray<TScriptInterface<class IDialogueExecutionHandler>> GetDialogueDelegates();
	

	//Dialogue System
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(class UDialogueAsset* InDialogueAsset = nullptr, AActor* InOwner = nullptr, APlayerController* InPlayerController =
		                   nullptr);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void DialogueBPFunction(const FString& ActionData);
	
	
	void SaveDialogue();
	void LoadDialogue();

	
	void UnregisterAllStateData();
	
private:
	TMap<FSoftObjectPath, FStateData> DialogueTreeStates;
};


