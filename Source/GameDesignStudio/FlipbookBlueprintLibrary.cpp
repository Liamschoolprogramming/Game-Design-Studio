#include "FlipbookBlueprintLibrary.h"

#include <string>

#include "MeshPaintVisualize.h"
#include "PaperSprite.h"

TMap<UImage*, FFlipbookInfo> UFlipbookBlueprintLibrary::FlipbookInfo;

/** 
 * @param Sprite 
 * @return Texture2D for the given PaperSprite
 */
UTexture2D* UFlipbookBlueprintLibrary::GetSpriteTexture(UPaperSprite* Sprite)
{
	if (!Sprite) return nullptr;
	return Sprite->GetBakedTexture();
}

/** 
 * Gets the Flipbook animation info for the given Image Widget
 * @param Image Image Widget 
 * @return FFlipbookInfo for the given Image Widget
 */
FFlipbookInfo& UFlipbookBlueprintLibrary::GetFlipbookInfo(UImage* Image)
{
	return FlipbookInfo.FindOrAdd(Image);
}

/** 
 * Plays the given flipbook in the given Image Widget. Upon completion, OnFinished is called.
 * @param Image Image Widget
 * @param Flipbook Flipbook to play
 * @param OnFinished Callback function to be triggered upon flipbook completion
 * @return FFlipbookInfo for the given Image Widget
 */
void UFlipbookBlueprintLibrary::PlayFlipbook(UImage* Image, UPaperFlipbook* Flipbook, FOnFlipbookFinished OnFinished)
{
	FFlipbookInfo& Info = GetFlipbookInfo(Image);
	
	Info.bAnimating = true;
	Info.ActiveFlipbook = Flipbook;
	Info.CurrentFrame = 0;
	Info.TotalFrames =  Flipbook->GetNumKeyFrames();
	Info.OnFinished = OnFinished;
	UpdateFrame(Image);
	
	UWorld* World = Image->GetWorld();
	
	if (Info.TimerHandle.IsValid())
	{
		World->GetTimerManager().ClearTimer(Info.TimerHandle);
	}
	
	float TickRate =  1.0 / Info.ActiveFlipbook->GetFramesPerSecond();
	
	World->GetTimerManager().SetTimer(
		Info.TimerHandle,
		FTimerDelegate::CreateLambda([Image](){TickFlipbook(Image);}),
		TickRate,
		true
	);
}

/** 
 * Increments one frame of the active Flipbook for the given Image Widget.
 * @param Image Image Widget
 */
void UFlipbookBlueprintLibrary::TickFlipbook(UImage* Image)
{
	FFlipbookInfo& Info = GetFlipbookInfo(Image);
	Info.CurrentFrame++;
	
	UWorld* World = Image->GetWorld();
	
	if (Info.CurrentFrame >= Info.TotalFrames)
	{
		World->GetTimerManager().ClearTimer(Info.TimerHandle);
		Info.bAnimating = false;

		if (Info.OnFinished.IsBound())
		{
			Info.OnFinished.Execute();
		}
	}
	else
	{
		UpdateFrame(Image);
	}
}

/** 
 * Updates the Image Widget's brush to the current frame of its Flipbook
 * @param Image Image Widget
 */
void UFlipbookBlueprintLibrary::UpdateFrame(UImage* Image)
{
	FFlipbookInfo& Info = GetFlipbookInfo(Image);
	
	if (Info.ActiveFlipbook != nullptr)
	{
		UPaperSprite* Sprite = Info.ActiveFlipbook->GetSpriteAtFrame(Info.CurrentFrame);
		if (Sprite)
		{
			Image->SetBrushFromTexture(Sprite->GetBakedTexture());
		}
	}
}


