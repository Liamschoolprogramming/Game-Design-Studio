#include "FlipbookBlueprintLibrary.h"
#include "PaperSprite.h"

UTexture2D* UFlipbookBlueprintLibrary::GetSpriteTexture(UPaperSprite* Sprite)
{
	if (!Sprite) return nullptr;
	return Sprite->GetBakedTexture();
}