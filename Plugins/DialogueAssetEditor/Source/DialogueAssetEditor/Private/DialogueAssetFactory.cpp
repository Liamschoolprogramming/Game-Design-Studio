#include "DialogueAssetFactory.h"

#include "DialogueAsset.h"

UDialogueAssetFactory::UDialogueAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UDialogueAsset::StaticClass();
}

UObject* UDialogueAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UDialogueAsset* Asset = NewObject<UDialogueAsset>(InParent, InName, Flags);
	return Asset;
}

bool UDialogueAssetFactory::CanCreateNew() const
{
	return true;
}
