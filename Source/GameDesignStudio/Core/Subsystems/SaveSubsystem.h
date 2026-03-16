// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "Core/ELSGameInstance.h"
#include "Core/ELSSaveGame.h"
#include "Core/MetaSave.h"
#include "GameFramework/SaveGame.h"
#include "SaveSubsystem.generated.h"

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
	
	FSaveData PrepareSaveData();
	void ConvertSaveData(const FSaveData& SaveData) const;

	static void CaptureToTexture(const FString& SlotName);
	UFUNCTION(BlueprintCallable, Category = "Texture")
	static UTexture2D* LoadTexture2DFromFile(const FString& FilePath);
	
	UFUNCTION(BlueprintCallable)
	bool SaveAllGameSubsystems(bool bIsAutoSave = false, FString SlotName = FString(TEXT("default")), bool bOverrideSave = false);
	
	UFUNCTION(BlueprintCallable)
	TArray<UELSSaveGame*> GetAllGameSaves();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxAutoSaves = 4;
	
	
	UFUNCTION(BlueprintCallable)
	float GetTimeTillAutoSave() const;
	UFUNCTION(BlueprintCallable)
	float GetTimeElapsedSinceAutoSave() const;
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void AutoSave();
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void DeleteSaveSlot(FString SlotName);
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetAutoSaveFrequency(float InTimeThreshold);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save")
	//in seconds
	float AutoSaveFrequency =  600.f;
	
	
	FTimerHandle AutoSaveTimerHandle;
	
	FTimerDelegate AutoSaveTimerDelegate;
	
	UFUNCTION(BlueprintCallable)
	static void SaveGameManager();
	
	UFUNCTION(BlueprintCallable)
	static void SavePuzzleWorld();
	UFUNCTION(BlueprintCallable)
	static void SavePlayer();
	UFUNCTION(BlueprintCallable)
	static void SaveDialogue();
	UFUNCTION(BlueprintCallable)
	static void SaveQuests();
	
};

