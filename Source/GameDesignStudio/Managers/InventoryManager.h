// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Data/PlayerStats.h"
#include "UObject/Object.h"
#include "InventoryManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UInventoryManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FPlayerInventoryItem> PlayerInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FPlayerInventoryItem> AllItems;
	
	UFUNCTION(BlueprintCallable)
	bool AddToInventory(FName ItemName, int Amount);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveFromInventory(FName ItemName, int Amount);

	UFUNCTION(BlueprintCallable)
	void SetMaxAmountForItem(FName ItemName, int MaxAmount);
};
