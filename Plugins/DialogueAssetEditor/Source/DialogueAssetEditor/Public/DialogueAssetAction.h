#pragma once
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FDialogueAssetAction : public FAssetTypeActions_Base
{
	//register asset
public:
	FDialogueAssetAction(EAssetTypeCategories::Type Category);

public: //FAssetTypeActions_Base interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type AssetCategory;
};