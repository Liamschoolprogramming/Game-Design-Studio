#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AutoSaveWarningController.generated.h"

UCLASS()
class UAutoSaveWarningController : public UUserWidget {
    GENERATED_BODY()

public: // Methods
    UAutoSaveWarningController(const FObjectInitializer& objectInitializer);
    virtual ~UAutoSaveWarningController() { }

public: // Create Method
    static UAutoSaveWarningController* CreateInstance(APlayerController* playerController);

public: // Properties
// ---------- Generated Properties Section ---------- //
//              (Don't modify manually)               //
// ---------- End Generated Properties Section ---------- //
};

// ---------- Generated Loader Section ---------- //
//             (Don't modify manually)            //
UCLASS()
class UAutoSaveWarningLoader : public UObject {
    GENERATED_BODY()
public:
    UAutoSaveWarningLoader();
    virtual ~UAutoSaveWarningLoader() { }

public:
    UPROPERTY()
    UClass* WidgetTemplate = nullptr;
    static const inline FString WidgetPath = TEXT("/Game/GameDesignStudio/UI/SaveMenu/WBP_AutoSaveWarning");
};
// ---------- End Generated Loader Section ---------- //
