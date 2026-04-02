// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "SaveLoadIndicatorController.h"
#include "Core/ELSGameInstance.h"
#include "Core/ELSSaveGame.h"
#include "Core/MetaSave.h"
#include "Data/PuzzleWorldData.h"
#include "GameFramework/SaveGame.h"
#include "SaveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveFinish);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite)
	FRotator PlayerRotation;
};

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void FindAllSubsystems();
	
	UPROPERTY()
	TMap<FName, UGameInstanceSubsystem*> Subsystems;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMetaSave* MetaSave;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UELSSaveGame* SaveGame;
	
	class UGameManagerSubsystem* GameManagerSubsystem;
	class UDialogueSubsystem* DialogueSubsystem;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FOnSaveStart OnSaveStart;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FOnSaveFinish OnSaveFinish;
	USaveLoadIndicatorController* SaveIndicator;

	UFUNCTION(BlueprintCallable, Category = "SaveSubsystem")
	static bool DoesSaveExist(const FString& SaveName);

	void CreateSaveIndicator();
	void DestroySaveIndicator();
	
	void Save(bool bInIsAutoSave, const FString& SlotName, const FString& SaveSlotPath);

	void SaveMeta();
	
	FSaveData PrepareSaveData();
	void ConvertSaveData(const FSaveData& SaveData) const;

	static void CaptureToTexture(const FString& SlotName);
	UFUNCTION(BlueprintCallable, Category = "Texture")
	static UTexture2D* LoadTexture2DFromFile(const FString& FilePath);
	
	UFUNCTION(BlueprintCallable)
	bool SaveAllGameSubsystems(bool bIsAutoSave = false, FString SlotName = FString(TEXT("default")), bool bOverrideSave = false);
	
	UFUNCTION(BlueprintCallable)
	TArray<UELSSaveGame*> GetAllGameSaves() const;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxAutoSaves = 4;
	
	
	
	UFUNCTION(BlueprintCallable)
	float GetTimeTillAutoSave() const;
	UFUNCTION(BlueprintCallable)
	float GetTimeElapsedSinceAutoSave() const;
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void AutoSave();

	UFUNCTION(BlueprintCallable, Category = "Save")
	UELSSaveGame* LoadGame(FString SlotName);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadPuzzles();
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void DeleteSaveSlot(FString SlotName) const;
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void CreateSaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetAutoSaveFrequency(float InTimeThreshold);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	//in seconds
	float AutoSaveFrequency =  600.f;
	
	
	FTimerHandle AutoSaveTimerHandle;
	
	FTimerDelegate AutoSaveTimerDelegate;
	
	TMap<FName,FPuzzleWorldData> PuzzleWorldData;
	
	UFUNCTION(BlueprintCallable)
	static void SaveGameManager();
	
	UFUNCTION(BlueprintCallable)
	void SavePuzzleWorld();
	UFUNCTION(BlueprintCallable)
	void SavePlayer();
	UFUNCTION(BlueprintCallable)
	FPlayerData LoadPlayer();
	UFUNCTION(BlueprintCallable)
	void SaveDialogue();
	UFUNCTION(BlueprintCallable)
	void SaveQuests();
	UFUNCTION(BlueprintCallable)
	bool LoadQuests();
	
	
	
};


