// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManagerSubsystem.generated.h"

/**
 * 
 */

//**************************************************//
//		RENAME THIS TO PuzzleProgressSubsystem		//
//**************************************************//

class UGameManagerBase;

UCLASS()
class GAMEDESIGNSTUDIO_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public: 
	
	// Manages the subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	template<typename T>
	T* GetManager() const;
	
	// Template is used for the UClass type
	UFUNCTION(BlueprintPure, Category = "Managers")
	UGameManagerBase* GetManager(TSubclassOf<UGameManagerBase> ManagerClass) const;
	
protected:
	
	virtual void RegisterManagers();
	
	template<typename T>
	void RegisterManager();
	
private:
	
	// Map for access to managers
	UPROPERTY(EditDefaultsOnly, Category = "GameManager")
	TMap<TSubclassOf<UGameManagerBase>, TObjectPtr<UGameManagerBase>> Managers;
	
};
