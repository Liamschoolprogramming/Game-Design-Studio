
#pragma once

#include "CoreMinimal.h"
#include "Core/Puzzles/Puzzle.h"

#include "PuzzleInventoryManager.generated.h"

UENUM(Blueprintable)
enum class EPuzzleInventoryItem : uint8
{
	Preserver UMETA(DisplayName = "Preserver"),
	Inverter UMETA(DisplayName = "Inverter"),
	Prism UMETA(DisplayName = "Prism"),
	Boulder UMETA(DisplayName = "Boulder")
};

USTRUCT(BlueprintType)
struct FPuzzleInventoryItem : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	EPuzzleInventoryItem Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TSubclassOf<APuzzle> PuzzleItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
};

USTRUCT(BlueprintType)
struct FPuzzleInventorySlotItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int SlotIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FPuzzleInventoryItem PuzzleInventoryItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	APuzzle* PuzzleItemRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	bool bInLevel;
};

UCLASS()
class GAMEDESIGNSTUDIO_API UPuzzleInventoryManager : public UGameManagerBase
{
	GENERATED_BODY()

public:
	UPuzzleInventoryManager();
	
	UFUNCTION(BlueprintCallable)
	int GetMaxSlots();
	
	UFUNCTION(BlueprintCallable)
	void UnlockPuzzleItem(FPuzzleInventoryItem PuzzleItem);
	
	UFUNCTION(BlueprintCallable)
	void SetPuzzleSlot(FPuzzleInventoryItem PuzzleItem, int SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	void ClearPuzzleSlots();
	
	UFUNCTION(BlueprintCallable)
	void ResetAllPuzzleSlotsToNotInLevel();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickupPuzzleItem(APuzzle* PuzzleItem);
	
	UFUNCTION(BlueprintCallable)
	void AddPuzzleInventorySlot();
	
	UFUNCTION(BlueprintCallable)
	FPuzzleInventorySlotItem GetPuzzleInventorySlotItem(int SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	TArray<FPuzzleInventorySlotItem> GetPuzzleInventorySlots();
	
	UFUNCTION(BlueprintCallable)
	TArray<FPuzzleInventoryItem> GetAvailablePuzzleItems();

private:
	// all available unlocked puzzle items
	UPROPERTY(SaveGame)
	TArray<FPuzzleInventoryItem> PuzzleItems;
	
	// puzzle elements "equipped" by player or in level
	UPROPERTY(SaveGame)
	TArray<FPuzzleInventorySlotItem> PuzzleInventorySlots;
	
	int MaxSlots = 3;
};
