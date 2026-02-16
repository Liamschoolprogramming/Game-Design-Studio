// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditor.h"
#include "CustomAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

class SCustomGraphPin :public SGraphPin
{
	public:
	SLATE_BEGIN_ARGS(SCustomGraphPin){}
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	
	protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(.2f,1.0f,0.2f));
	}
};

struct FCustomPinFactory : public FGraphPanelPinFactory
{
	public:
	virtual ~FCustomPinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("CustomPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SCustomGraphPin, Pin);
		}
		return nullptr;
	}
};

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
	FSlateImageBrush* NodeAddPinIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeAddPinIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* NodeDeletePinIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeletePinIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* NodeDeleteNodeIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeleteNodeIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	StyleSet->Set(TEXT("ClassThumbnail.CustomAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.CustomAsset"), IconBrush);
	StyleSet->Set(TEXT("CustomAssetEditor.NodeAddPinIcon"), NodeAddPinIcon);
	StyleSet->Set(TEXT("CustomAssetEditor.NodeDeletePinIcon"), NodeDeletePinIcon);
	StyleSet->Set(TEXT("CustomAssetEditor.NodeDeleteNodeIcon"), NodeDeleteNodeIcon);
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	
	CustomPinFactory = MakeShareable(new FCustomPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(CustomPinFactory);
}

void FCustomAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(CustomPinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)