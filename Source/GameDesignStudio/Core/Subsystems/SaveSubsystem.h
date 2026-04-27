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

DEFINE_LOG_CATEGORY_STATIC(FSaveSubsystemLog, Log, All)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAutoSaveWarning);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite)
	FRotator PlayerRotation;
	UPROPERTY(BlueprintReadWrite)
	TArray<EPlayerCharacterType> UnlockedPossessables;
};

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API USaveSubsystem : public UGameInstanceSubsystem, public FTickableGameObject	
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
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FAutoSaveWarning AutoSaveWarning;

	UFUNCTION(BlueprintCallable, Category = "SaveSubsystem")
	static bool DoesSaveExist(const FString& SaveName);

	UFUNCTION(BlueprintCallable, Category = "SaveSubsystem")
	void CreateSaveIndicator();
	UFUNCTION()
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
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetMaxAutoSaves(int32 NewMax);
	
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

	UFUNCTION(BlueprintCallable)
	void SaveRespawn();

	UFUNCTION(BlueprintCallable)
	bool LoadRespawn();
	
private:
	bool HasNotifiedAutoSaveWarning;
protected:
	// FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UMyTickableSubsystem, STATGROUP_Tickables); }

	// Optional overrides
	virtual bool IsTickable() const override { return !IsTemplate(); }
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }

};


