#pragma once

#include "CoreMinimal.h"
#include "DialogueAssetFactory.generated.h"

UCLASS()
class UDialogueAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UDialogueAssetFactory(const FObjectInitializer& ObjectInitializer);

public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
};