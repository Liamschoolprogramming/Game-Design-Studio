#include "DialogueAssetAction.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorApp.h"

FDialogueAssetAction::FDialogueAssetAction(EAssetTypeCategories::Type Category)
{
	AssetCategory = Category;
	
}

FText FDialogueAssetAction::GetName() const
{
	return FText::FromString(TEXT("Dialogue Asset"));
}

FColor FDialogueAssetAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FDialogueAssetAction::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

void FDialogueAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		UDialogueAsset* Asset = Cast<UDialogueAsset>(Object);
		if (Asset != nullptr)
		{
			TSharedRef<FDialogueAssetEditorApp> EditorApp(new FDialogueAssetEditorApp());
			EditorApp->InitEditor(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

uint32 FDialogueAssetAction::GetCategories()
{
	return AssetCategory;
}
