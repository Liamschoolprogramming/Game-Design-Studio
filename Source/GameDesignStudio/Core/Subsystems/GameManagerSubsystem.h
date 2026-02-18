// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Managers/InventoryManager.h"
#include "Managers/PlayerStatManager.h"
#include "Managers/PuzzleRiverManager.h"
#include "Managers/QuestManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManagerSubsystem.generated.h"

/**
 * 
 */

class UGameManagerBase;

UCLASS()
class GAMEDESIGNSTUDIO_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public: 
	
	// Manages the subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	// These should be in the manager baseclass that return a boolean if the puzzle is complete
	// or not. It should do a check on the managers data if it has all states needed to return true
	void IsPuzzleSolved(FString Id);
	void SetStepComplete(FString Id, FString Step);
	
	void SetPuzzleState(TSubclassOf<UGameManagerBase> ManagerClass, FName StateId);
	
	template<typename T>
	T* GetManager();
	
	// For blueprints and when the type needs to be infered at runtime
	UFUNCTION(BlueprintCallable, Category = "Managers", meta = (DeterminesOutputType = "ManagerClass"))
	UGameManagerBase* GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass);
	
	// Stricter type safety for C++ for getting a manager from the list of managers
	UGameManagerBase* GetManager(TSubclassOf<UGameManagerBase> ManagerClass) const;
	
	// For calling in C++ just pass in the this keyword for the argument. Do not call on beginplay
	UFUNCTION(BlueprintCallable, Category = "Managers", meta = (DefaultToSelf = "Actor"))
	void SnapshotActorValues(APuzzle* Actor);
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UPuzzleRiverManager* GetPuzzleRiverManager() const;
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UInventoryManager* GetInventoryManager() const;
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UPlayerStatManager* GetPlayerStatManager() const;
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UQuestManager* GetQuestManager() const;
	
	void RegisterActorToManager(TSubclassOf<UGameManagerBase> ManagerClass, FName Id, const FPersistantActorValues& ActorValues);
	
	void LoadActor(TSubclassOf<UGameManagerBase> ManagerClass, FName Id, const FPersistantActorValues& ActorValues);
	
	UPROPERTY()
	FPlayerStats PlayerStats;
	
protected:
	
	virtual void RegisterManagers();
	
	template<typename T>
	void RegisterManager();
	
private:
	
	// Map for access to managers
	UPROPERTY(EditDefaultsOnly, Category = "GameManager")
	TMap<TSubclassOf<UGameManagerBase>, TObjectPtr<UGameManagerBase>> Managers;
	
};
