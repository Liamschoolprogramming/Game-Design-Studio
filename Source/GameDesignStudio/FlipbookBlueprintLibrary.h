#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FlipbookBlueprintLibrary.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API UFlipbookBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Paper2D")
	static UTexture2D* GetSpriteTexture(class UPaperSprite* Sprite);
};