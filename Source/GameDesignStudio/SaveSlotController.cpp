#include "SaveSlotController.h"

// ---------- Generated Includes Section ---------- //
//             (Don't modify manually)              //
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
// ---------- End Generated Includes Section ---------- //

USaveSlotController::USaveSlotController(const FObjectInitializer& objectInitializer) : UUserWidget(objectInitializer) {

}

// ---------- Generated Methods Section ---------- //
//             (Don't modify manually)             //
USaveSlotController* USaveSlotController::CreateInstance(APlayerController* playerController) {
    USaveSlotLoader* loader = NewObject<USaveSlotLoader>(playerController);
    return Cast<USaveSlotController>(CreateWidget(playerController, loader->WidgetTemplate));
}

USaveSlotLoader::USaveSlotLoader() {
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetTemplateFinder(*WidgetPath);
    WidgetTemplate = widgetTemplateFinder.Class;
}
// ---------- End Generated Methods Section ---------- //
