// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditor.h"
#include "CustomAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

void FCustomAssetEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("CustomAssets")), FText::FromString(TEXT("Custom Assets")));
	TSharedPtr<FCustomAssetAction> CustomAssetAction = MakeShareable(new FCustomAssetAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(CustomAssetAction.ToSharedRef());
	
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("CustomAssetEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("CustomAssetEditor"));
	FString ContentDirectory = Plugin->GetContentDir();
	StyleSet->SetContentRoot(ContentDirectory);
	
	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("CustomAssetThumbnail"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("CustomAssetIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	StyleSet->Set(TEXT("ClassThumbnail.CustomAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.CustomAsset"), IconBrush);
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FCustomAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)