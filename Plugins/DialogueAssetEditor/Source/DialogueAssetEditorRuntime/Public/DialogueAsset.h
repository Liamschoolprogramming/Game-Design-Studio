#pragma once
#include <functional>

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include <functional>
#include "DialogueAsset.generated.h"


UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueAsset : public UObject
{
	
	GENERATED_BODY()
	
public: //properties
	UPROPERTY(EditAnywhere)
	FString DialogueName = TEXT("Enter dialogue name here");
	
	
	
	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;
	
public: //dialogue interface
	void SetPreSaveListener(std::function<void()> OnPreSaveListenerIn) {OnPreSaveListener = OnPreSaveListenerIn;}
	
public: //UObject interface
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
	
private: //members
	std::function<void()> OnPreSaveListener = nullptr;
};
