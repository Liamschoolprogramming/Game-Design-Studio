#include "QuestDialogueUIController.h"

// ---------- Generated Includes Section ---------- //
//             (Don't modify manually)              //
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
// ---------- End Generated Includes Section ---------- //

UQuestDialogueUIController::UQuestDialogueUIController(const FObjectInitializer& objectInitializer) : UUserWidget(objectInitializer) {

}

// ---------- Generated Methods Section ---------- //
//             (Don't modify manually)             //
UQuestDialogueUIController* UQuestDialogueUIController::CreateInstance(APlayerController* playerController) {
    UQuestDialogueUILoader* loader = NewObject<UQuestDialogueUILoader>(playerController);
    return Cast<UQuestDialogueUIController>(CreateWidget(playerController, loader->WidgetTemplate));
}

UQuestDialogueUILoader::UQuestDialogueUILoader() {
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetTemplateFinder(*WidgetPath);
    WidgetTemplate = widgetTemplateFinder.Class;
}
// ---------- End Generated Methods Section ---------- //
