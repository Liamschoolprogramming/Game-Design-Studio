#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PaperFlipbook.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FlipbookBlueprintLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnFlipbookFinished);

USTRUCT(BlueprintType)
struct FFlipbookInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* ActiveFlipbook;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalFrames;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentFrame;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnFlipbookFinished OnFinished;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAnimating;
	
	FFlipbookInfo()
	{
		
		TotalFrames = 0;
		CurrentFrame = 0;
		bAnimating = false;
	}
	
	FFlipbookInfo(FTimerHandle TimerHandle, UPaperFlipbook* ActiveFlipbook, int TotalFrames, FOnFlipbookFinished OnFinished)
	{
		this->TimerHandle = TimerHandle;
		this->ActiveFlipbook = ActiveFlipbook;
		this->TotalFrames = TotalFrames;
		this->OnFinished = OnFinished;
		this->CurrentFrame = 0;
		this->bAnimating = false;
	}
};

UCLASS()
class GAMEDESIGNSTUDIO_API UFlipbookBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(Category = "Paper2D")
	static void TickFlipbook(UImage* Image);
	
	UFUNCTION(Category = "Paper2D")
	static void UpdateFrame(UImage* Image);
	
public:
	static TMap<UImage*, FFlipbookInfo> FlipbookInfo;
	
	UFUNCTION(BlueprintCallable, Category = "Paper2D")
	static UTexture2D* GetSpriteTexture(class UPaperSprite* Sprite);
	
	UFUNCTION(BlueprintCallable, Category = "Paper2D", meta=(WorldContext = "WorldContextObject"))
	static void PlayFlipbook(UImage* Image, UPaperFlipbook* Flipbook, FOnFlipbookFinished OnFinished);
	
	UFUNCTION(BlueprintCallable, Category = "Paper2D")
	static FFlipbookInfo& GetFlipbookInfo(UImage* Image);
};