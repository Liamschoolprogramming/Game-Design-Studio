// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PlayerStats.h"
#include "Managers/InventoryManager.h"
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
	
	template<typename T>
	T* GetManager();
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UGameManagerBase* GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass);
	
	// Template is used for the UClass type
	UGameManagerBase* GetManager(TSubclassOf<UGameManagerBase> ManagerClass) const;
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UPuzzleRiverManager* GetPuzzleRiverManager() const;
	
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UInventoryManager* GetInventoryManager() const;
	
	void RegisterActorToManager(TSubclassOf<UGameManagerBase> ManagerClass, FName Id, const FPersistantActorValues& ActorValues);
		
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
