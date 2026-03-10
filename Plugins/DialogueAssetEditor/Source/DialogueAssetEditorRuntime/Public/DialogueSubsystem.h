// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSubsystem.generated.h"


class UDialogueAsset;
class UDialogueSave;

UENUM(BlueprintType)
enum class EStates : uint8
{
	NotStarted,
	Finished,
	FinishedWithTag
};

USTRUCT()
struct FStateData
{
	GENERATED_BODY()

	UPROPERTY()
	EStates State;
	UPROPERTY()
	FString Tag;
};

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
	
	void SaveDialogue();
	void LoadDialogue();

	
	void UnregisterAllStateData();
	
private:
	TMap<FSoftObjectPath, FStateData> DialogueTreeStates;
};


