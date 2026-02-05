#include "CustomAssetAction.h"
#include "CustomAsset.h"
#include "CustomAssetEditorApp.h"

FCustomAssetAction::FCustomAssetAction(EAssetTypeCategories::Type Category)
{
	AssetCategory = Category;
	
}

FText FCustomAssetAction::GetName() const
{
	return FText::FromString(TEXT("Custom Asset"));
}

FColor FCustomAssetAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FCustomAssetAction::GetSupportedClass() const
{
	return UCustomAsset::StaticClass();
}

void FCustomAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		UCustomAsset* Asset = Cast<UCustomAsset>(Object);
		if (Asset != nullptr)
		{
			TSharedRef<FCustomAssetEditorApp> EditorApp(new FCustomAssetEditorApp());
			EditorApp->InitEditor(Mode, EditWithinLevelEditor, Asset);
		}
	}
}

uint32 FCustomAssetAction::GetCategories()
{
	return AssetCategory;
}
