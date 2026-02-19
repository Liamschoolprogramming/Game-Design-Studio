
#pragma once

#include "CoreMinimal.h"
#include "PuzzleEmitter.h"
#include "PuzzleInteractive.h"
#include "GameFramework/Actor.h"
#include "PuzzleInteractiveEmitter.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleInteractiveEmitter : public APuzzleInteractive
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable) 
	void EmitGreenSignal();
	
	UFUNCTION(BlueprintCallable) 
	void EmitRedSignal();


public:
	APuzzleInteractiveEmitter();
	
	virtual void Interact(APlayerCharacter* PlayerCharacter) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (
		InstanceEditable = "true", ExposeOnSpawn = "true"))
	float EmitSignalTimerDuration;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) 
	void SetActivatedState(bool ActiveState);

protected:
	FTimerHandle EmitSignalTimer;
};
