#include "FlipbookBlueprintLibrary.h"
#include "PaperSprite.h"

UTexture2D* UFlipbookBlueprintLibrary::GetSpriteTexture(UPaperSprite* Sprite)
{
	if (!Sprite) return nullptr;
#if WITH_EDITOR
	return Sprite->GetSourceTexture();
#else
	return nullptr;
#endif
}