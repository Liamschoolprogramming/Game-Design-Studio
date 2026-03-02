// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueAssetEditor.h"
#include "DialogueAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "CompleteQuestGraphNode.h"
#include "CheckQuestGraphNode.h"
#include "DialogueEndGraphNode.h"
#include "DialogueGraphNode.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphNodeFactory.h"
#include "DialogueStartGraphNode.h"
#include "Styling/SlateStyleRegistry.h"
#include "EdGraphUtilities.h"
#include "QuestProgressGraphNode.h"
#include "RandomDialogueGraphNode.h"
#include "StartQuestGraphNode.h"
#include "UnrealEdGlobals.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"
#include "Editor/UnrealEdEngine.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FDialogueAssetEditorModule"





/**
 * Defines the custom pin type used for the dialogue nodes
 */
class SDialogueGraphPin :public SGraphPin
{
	public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin){}
		
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
class SDialogueStartGraphPin :public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin){}
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(1.f,0.2f,0.2f));
	}
};

class SDialogueCheckQuestGraphPin :public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin){}
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(1, 0.914, 0.624));
	}
};

class SDialogueEndGraphPin :public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin){}
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
	
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.2f,0.2f,1.f));
	}
};

/**
 * Defines the pin factory for the custom pins
 */
struct FDialoguePinFactory : public FGraphPanelPinFactory
{
	public:
	virtual ~FDialoguePinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("DialoguePin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueGraphPin, Pin);
		} else if(FName(TEXT("StartPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueStartGraphPin, Pin);
		} else if(FName(TEXT("Quest")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueCheckQuestGraphPin, Pin);
		} else if(FName(TEXT("EndPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueStartGraphPin, Pin);
		}
		return nullptr;
	}
};


/**
 * Register and load everything in the editor module
 * 
 */
void FDialogueAssetEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("DialogueAssets")), FText::FromString(TEXT("Dialogue Assets")));
	TSharedPtr<FDialogueAssetAction> DialogueAssetAction = MakeShareable(new FDialogueAssetAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(DialogueAssetAction.ToSharedRef());
	
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogueAssetEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("DialogueAssetEditor"));
	FString ContentDirectory = Plugin->GetContentDir();
	StyleSet->SetContentRoot(ContentDirectory);
	
	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetThumbnail"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* NodeAddPinIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeAddPinIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* NodeDeletePinIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeletePinIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	FSlateImageBrush* NodeDeleteNodeIcon = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeleteNodeIcon"), TEXT(".png")), FVector2D(512.0, 512.0));
	StyleSet->Set(TEXT("ClassThumbnail.DialogueAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.DialogueAsset"), IconBrush);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeAddPinIcon"), NodeAddPinIcon);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeDeletePinIcon"), NodeDeletePinIcon);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeDeleteNodeIcon"), NodeDeleteNodeIcon);
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	
	DialoguePinFactory = MakeShareable(new FDialoguePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(DialoguePinFactory);
	
	
	
	
}

/**
 * Deconstructor
 */
void FDialogueAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(DialoguePinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueAssetEditorModule, DialogueAssetEditor)