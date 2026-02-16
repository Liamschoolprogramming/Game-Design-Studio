#pragma once


#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "CustomRuntimeGraph.generated.h"

UCLASS()
class CUSTOMASSETEDITORRUNTIME_API  UCustomeRuntimePin: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PinName;
	
	UPROPERTY()
	FGuid PinId;
	
	UPROPERTY()
	UCustomeRuntimePin* Connection = nullptr;
};

UCLASS()
class CUSTOMASSETEDITORRUNTIME_API  UCustomRuntimeNode: public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	UCustomeRuntimePin* InputPin;
	
	UPROPERTY()
	TArray<UCustomeRuntimePin*> OutputPins;
	
	UPROPERTY()
	FVector2D Position;
};

UCLASS()
class CUSTOMASSETEDITORRUNTIME_API  UCustomRuntimeGraph: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<UCustomRuntimeNode*> Nodes;
};