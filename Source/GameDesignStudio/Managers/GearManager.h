#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Managers/InventoryManager.h"
#include "GearManager.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API UGearManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FPlayerInventoryItem> PlayerGear;
	
	UFUNCTION(BlueprintCallable)
	FPlayerInventoryItem EquipGear(FPlayerInventoryItem Gear);
	
	UFUNCTION(BlueprintCallable)
	FPlayerInventoryItem UnequipGear(EGearType GearType);
	
	UFUNCTION(Blueprintable)
	void ApplyGearStats(FPlayerInventoryItem Gear);
	
	UFUNCTION(Blueprintable)
	void RemoveGearStats(FPlayerInventoryItem Gear);
};