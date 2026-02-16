#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class FDialogueAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook 
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InObject);
	
	class UDialogueAsset* GetWorkingAsset()
	{
		return WorkingAsset;
	}
	
	class UEdGraph* GetWorkingGraph()
	{
		return WorkingGraph;
	}

public: //FAssetEditorToolkit interface
	virtual FText GetToolkitName() const override
	{
		return FText::FromString(TEXT("DialogueAssetEditorApp"));
	}
	virtual FName GetToolkitFName() const override
	{
		return FName(TEXT("DialogueAssetEditorApp"));
	}
	virtual FText GetBaseToolkitName() const override
	{
		return FText::FromString(TEXT("DialogueAssetEditorApp"));
	}
	virtual FString GetWorldCentricTabPrefix() const override
	{
		return TEXT("DialogueAssetEditorApp");
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
	
	virtual void OnClose() override;
	void OnGraphChanged(const FEdGraphEditAction& EditAction);
	
protected:
	void UpdateWorkingAssetFromGraph();
	void UpdateEditorGraphFromWorkingAsset();
	
private:
	UPROPERTY()
	UDialogueAsset* WorkingAsset = nullptr;
	
	UPROPERTY()
	class UEdGraph* WorkingGraph = nullptr;
	
	FDelegateHandle GraphChangedListenerHandle;
};