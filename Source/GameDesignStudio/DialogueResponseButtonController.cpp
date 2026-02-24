#include "DialogueResponseButtonController.h"

// ---------- Generated Includes Section ---------- //
//             (Don't modify manually)              //
#include "Components/Button.h"
#include "Components/TextBlock.h"
// ---------- End Generated Includes Section ---------- //

UDialogueResponseButtonController::UDialogueResponseButtonController(const FObjectInitializer& objectInitializer) : UUserWidget(objectInitializer) {

}

void UDialogueResponseButtonController::SetClickHandler(int InIndex, std::function<void(int)> InOnClickHandler)
{
    Index = InIndex;
    OnClickHandler = InOnClickHandler;
    
    ResponseButton->OnClicked.AddUniqueDynamic(this, &UDialogueResponseButtonController::OnButtonClicked);
}

void UDialogueResponseButtonController::OnButtonClicked()
{
    if (OnClickHandler)
    {
        OnClickHandler(Index);
    }
}

// ---------- Generated Methods Section ---------- //
//             (Don't modify manually)             //
UDialogueResponseButtonController* UDialogueResponseButtonController::CreateInstance(APlayerController* playerController) {
    UDialogueResponseButtonLoader* loader = NewObject<UDialogueResponseButtonLoader>(playerController);
    return Cast<UDialogueResponseButtonController>(CreateWidget(playerController, loader->WidgetTemplate));
}

UDialogueResponseButtonLoader::UDialogueResponseButtonLoader() {
    static ConstructorHelpers::FClassFinder<UUserWidget> widgetTemplateFinder(*WidgetPath);
    WidgetTemplate = widgetTemplateFinder.Class;
}
// ---------- End Generated Methods Section ---------- //
