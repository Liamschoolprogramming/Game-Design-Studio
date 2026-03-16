#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlotController.generated.h"

UCLASS()
class USaveSlotController : public UUserWidget {
    GENERATED_BODY()

public: // Methods
    USaveSlotController(const FObjectInitializer& objectInitializer);
    virtual ~USaveSlotController() { }

public: // Create Method
    static USaveSlotController* CreateInstance(APlayerController* playerController);

public: // Properties
// ---------- Generated Properties Section ---------- //
//              (Don't modify manually)               //
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* SlotButton = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* NumberImage = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* NameBG = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* SaveName = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* SpacerBG = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* DateSaved = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* DeleteSlotButton = nullptr;
// ---------- End Generated Properties Section ---------- //
};

// ---------- Generated Loader Section ---------- //
//             (Don't modify manually)            //
UCLASS()
class USaveSlotLoader : public UObject {
    GENERATED_BODY()
public:
    USaveSlotLoader();
    virtual ~USaveSlotLoader() { }

public:
    UPROPERTY()
    UClass* WidgetTemplate = nullptr;
    static const inline FString WidgetPath = TEXT("/Game/GameDesignStudio/UI/SaveMenu/WBP_SaveSlot");
};
// ---------- End Generated Loader Section ---------- //
