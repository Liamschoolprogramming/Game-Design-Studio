#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "../PuzzleInteractive.h"
#include "GameFramework/Actor.h"
#include "PuzzleInteractive_Pickupable.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive_Pickupable : public APuzzleInteractive
{
	GENERATED_BODY()

public:
	APuzzleInteractive_Pickupable();
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Drop();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APlayerCharacter* CarryingCharacter;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bBeingCarried = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPushable = false;
	
	UPROPERTY(BlueprintReadOnly)
	FVector PushDirection;
	
protected:
	FVector Offset = FVector(200,200,0);
	
};
