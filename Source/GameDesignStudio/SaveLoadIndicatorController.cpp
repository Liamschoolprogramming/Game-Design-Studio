#include "SaveLoadIndicatorController.h"

// ---------- Generated Includes Section ---------- //
//             (Don't modify manually)              //
// ---------- End Generated Includes Section ---------- //

USaveLoadIndicatorController::USaveLoadIndicatorController(const FObjectInitializer& objectInitializer) : UUserWidget(objectInitializer) {

}

// ---------- Generated Methods Section ---------- //
//             (Don't modify manually)             //
USaveLoadIndicatorController* USaveLoadIndicatorController::CreateInstance(APlayerController* playerController) {
    USaveLoadIndicatorLoader* loader = NewObject<USaveLoadIndicatorLoader>(playerController);
    return Cast<USaveLoadIndicatorController>(CreateWidget(playerController, loader->WidgetTemplate));
}

USaveLoadIndicatorLoader::USaveLoadIndicatorLoader() {
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetTemplateFinder(*WidgetPath);
    WidgetTemplate = widgetTemplateFinder.Class;
}
// ---------- End Generated Methods Section ---------- //
