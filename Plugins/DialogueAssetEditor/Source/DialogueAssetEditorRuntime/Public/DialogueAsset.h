#pragma once
#include "CoreMinimal.h"
#include "DialogueRuntimeGraph.h"
#include "DialogueAsset.generated.h"


UCLASS(BlueprintType)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueAsset : public UObject
{
	
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString SomeData = TEXT("DefaultData");
	
	UPROPERTY(EditAnywhere)
	int32 SomeNumber = 0;
	
	UPROPERTY(EditAnywhere)
	bool SomeBool = false;
	
	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;
	
	
};
