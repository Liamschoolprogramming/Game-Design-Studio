
#pragma once

#include "CoreMinimal.h"
#include "PuzzleInteractive_Pickupable.h"
#include "UObject/Object.h"
#include "PuzzleInteractive_QuestItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive_QuestItem : public APuzzleInteractive
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FName InventoryItemName;
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
};
