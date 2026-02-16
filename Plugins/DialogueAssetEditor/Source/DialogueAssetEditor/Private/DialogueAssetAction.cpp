#include "DialogueAssetAction.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorApp.h"

/**
 * Create asset context action
 * @param Category how is the asset grouped in the editor menu
 */
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

/**
 * 
 * @return our asset class
 */
UClass* FDialogueAssetAction::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

/**
 * Used by unreal to handle opening the asset
 * 
 */
void FDialogueAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                           TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		UDialogueAsset* Asset = Cast<UDialogueAsset>(Object);
		if (Asset != nullptr)
		{
			//the magic happens here
			TSharedRef<FDialogueAssetEditorApp> EditorApp(new FDialogueAssetEditorApp());
			EditorApp->InitEditor(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

uint32 FDialogueAssetAction::GetCategories()
{
	return AssetCategory;
}
