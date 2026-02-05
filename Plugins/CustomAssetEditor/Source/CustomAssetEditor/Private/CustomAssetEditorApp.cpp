#include "CustomAssetEditorApp.h"

#include "CustomAssetAppMode.h"
#include "CustomAssetAppMode.h"
#include "CustomAsset.h"

void FCustomAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FCustomAssetEditorApp::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost,
	UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);
	
	WorkingAsset = Cast<UCustomAsset>(InObject);

	InitAssetEditor(
		Mode,
		InToolkitHost,
		TEXT("CustomAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true, //create standalone menu
		true, //create toolbar
		ObjectsToEdit
		);

	AddApplicationMode(TEXT("CustomAssetAppMode"), MakeShareable(new FCustomAssetAppMode(SharedThis(this))));

	SetCurrentMode(TEXT("CustomAssetAppMode"));
	
}
