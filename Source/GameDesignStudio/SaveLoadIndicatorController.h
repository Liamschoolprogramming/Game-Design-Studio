#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveLoadIndicatorController.generated.h"

UCLASS()
class USaveLoadIndicatorController : public UUserWidget {
    GENERATED_BODY()

public: // Methods
    USaveLoadIndicatorController(const FObjectInitializer& objectInitializer);
    virtual ~USaveLoadIndicatorController() { }

public: // Create Method
    static USaveLoadIndicatorController* CreateInstance(APlayerController* playerController);

public: // Properties
// ---------- Generated Properties Section ---------- //
//              (Don't modify manually)               //
// ---------- End Generated Properties Section ---------- //
};

// ---------- Generated Loader Section ---------- //
//             (Don't modify manually)            //
UCLASS()
class USaveLoadIndicatorLoader : public UObject {
    GENERATED_BODY()
public:
    USaveLoadIndicatorLoader();
    virtual ~USaveLoadIndicatorLoader() { }

public:
    UPROPERTY()
    UClass* WidgetTemplate = nullptr;
    static const inline FString WidgetPath = TEXT("/Game/GameDesignStudio/UI/SaveMenu/WBP_SaveLoadIndicator");
};
// ---------- End Generated Loader Section ---------- //
