#pragma once
#include <functional>

#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include <functional>

#include "DialogueCineCamera.h"
#include "DialogueAsset.generated.h"


UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueAsset : public UObject
{
	
	GENERATED_BODY()
	
public: //properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CameraActors;
	
	
	
	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;
	
public: //dialogue interface
	void SetPreSaveListener(std::function<void()> OnPreSaveListenerIn) {OnPreSaveListener = OnPreSaveListenerIn;}
	
public: //UObject interface
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
	
private: //members
	std::function<void()> OnPreSaveListener = nullptr;
};
