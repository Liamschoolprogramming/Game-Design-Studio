#include "CustomAssetFactory.h"

#include "CustomAsset.h"

UCustomAssetFactory::UCustomAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UCustomAsset::StaticClass();
}

UObject* UCustomAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UCustomAsset* Asset = NewObject<UCustomAsset>(InParent, InName, Flags);
	return Asset;
}

bool UCustomAssetFactory::CanCreateNew() const
{
	return true;
}
