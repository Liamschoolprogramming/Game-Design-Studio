#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "PuzzleInteractive.h"
#include "GameFramework/Actor.h"
#include "PuzzleInteractive_Pushable.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractive_Pushable : public APuzzleInteractive
{
	GENERATED_BODY()

public:
	APuzzleInteractive_Pushable();
	
	UFUNCTION(BlueprintCallable)
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APlayerCharacter* PushingCharacter;
	
protected:
	bool bBeingPushed = false;
	FVector Offset = FVector(100,100,0);
	
};
