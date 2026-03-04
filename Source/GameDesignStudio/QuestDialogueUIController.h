#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "QuestDialogueUIController.generated.h"

UCLASS()
class UQuestDialogueUIController : public UUserWidget {
    GENERATED_BODY()

public: // Methods
    UQuestDialogueUIController(const FObjectInitializer& objectInitializer);
    virtual ~UQuestDialogueUIController() { }

public: // Create Method
    static UQuestDialogueUIController* CreateInstance(APlayerController* playerController);

public: // Properties
// ---------- Generated Properties Section ---------- //
//              (Don't modify manually)               //
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* CharacterPortrait = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* CharacterName = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* DialogueText = nullptr;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UVerticalBox* ResponseBox = nullptr;
// ---------- End Generated Properties Section ---------- //
};

// ---------- Generated Loader Section ---------- //
//             (Don't modify manually)            //
UCLASS()
class UQuestDialogueUILoader : public UObject {
    GENERATED_BODY()
public:
    UQuestDialogueUILoader();
    virtual ~UQuestDialogueUILoader() { }

public:
    UPROPERTY()
    UClass* WidgetTemplate = nullptr;
    static const inline FString WidgetPath = TEXT("/Game/GameDesignStudio/UI/Dialogue/WBP_QuestDialogueUI");
};
// ---------- End Generated Loader Section ---------- //
