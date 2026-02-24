#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueResponseButtonController.generated.h"

UCLASS()
class UDialogueResponseButtonController : public UUserWidget {
    GENERATED_BODY()

public: // Methods
    UDialogueResponseButtonController(const FObjectInitializer& objectInitializer);
    virtual ~UDialogueResponseButtonController() { }
    
    void SetClickHandler(int InIndex, std::function<void(int)> InOnClickHandler);
    
    UFUNCTION()
    void OnButtonClicked();

public: // Create Method
    static UDialogueResponseButtonController* CreateInstance(APlayerController* playerController);

public: // Properties
// ---------- Generated Properties Section ---------- //
//              (Don't modify manually)               //
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UButton* ResponseButton = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* ResponseButtonText = nullptr;
// ---------- End Generated Properties Section ---------- //
    
    
private:
    int Index;
    std::function<void(int)> OnClickHandler;
};

// ---------- Generated Loader Section ---------- //
//             (Don't modify manually)            //
UCLASS()
class UDialogueResponseButtonLoader : public UObject {
    GENERATED_BODY()
public:
    UDialogueResponseButtonLoader();
    virtual ~UDialogueResponseButtonLoader() { }

public:
    UPROPERTY()
    UClass* WidgetTemplate = nullptr;
    static const inline FString WidgetPath = TEXT("/Game/GameDesignStudio/UI/Dialogue/WBP_DialogueResponseButton");
};
// ---------- End Generated Loader Section ---------- //
