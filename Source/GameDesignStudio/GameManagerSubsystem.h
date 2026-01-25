// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	template<typename T>
	T* GetManager() const;
	
	// For future deploy
	/*
	UFUNCTION(BlueprintCallable, Category = "Managers")
	UGameManagerBase* GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass) const;
	*/
	
protected:
	
	virtual void RegisterManagers();
	
	template<typename T>
	void RegisterManager();
	
private:
	
	// Map for manager lookup
	UPROPERTY()
	TMap<TSubclassOf<UGameManagerBase>, TObjectPtr<UGameManagerBase>> Managers;
	
};
