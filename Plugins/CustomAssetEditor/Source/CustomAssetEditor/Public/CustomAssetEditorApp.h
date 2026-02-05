#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class FCustomAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook 
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InObject);
	
	class UCustomAsset* GetWorkingAsset()
	{
		return WorkingAsset;
	}

public: //FAssetEditorToolkit interface
	virtual FText GetToolkitName() const override
	{
		return FText::FromString(TEXT("CustomAssetEditorApp"));
	}
	virtual FName GetToolkitFName() const override
	{
		return FName(TEXT("CustomAssetEditorApp"));
	}
	virtual FText GetBaseToolkitName() const override
	{
		return FText::FromString(TEXT("CustomAssetEditorApp"));
	}
	virtual FString GetWorldCentricTabPrefix() const override
	{
		return TEXT("CustomAssetEditorApp");
	}
	virtual FLinearColor GetWorldCentricTabColorScale() const override
	{
		return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
	}
	virtual FString GetDocumentationLink() const override
	{
		return TEXT("https://github.com/systeminabox");
	}
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override {}
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override {}
	
private:
	UPROPERTY()
	UCustomAsset* WorkingAsset = nullptr;
};