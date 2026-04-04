#include "AutoSaveWarningController.h"

// ---------- Generated Includes Section ---------- //
//             (Don't modify manually)              //
// ---------- End Generated Includes Section ---------- //

UAutoSaveWarningController::UAutoSaveWarningController(const FObjectInitializer& objectInitializer) : UUserWidget(objectInitializer) {

}

// ---------- Generated Methods Section ---------- //
//             (Don't modify manually)             //
UAutoSaveWarningController* UAutoSaveWarningController::CreateInstance(APlayerController* playerController) {
    UAutoSaveWarningLoader* loader = NewObject<UAutoSaveWarningLoader>(playerController);
    return Cast<UAutoSaveWarningController>(CreateWidget(playerController, loader->WidgetTemplate));
}

UAutoSaveWarningLoader::UAutoSaveWarningLoader() {
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetTemplateFinder(*WidgetPath);
    WidgetTemplate = widgetTemplateFinder.Class;
}
// ---------- End Generated Methods Section ---------- //
