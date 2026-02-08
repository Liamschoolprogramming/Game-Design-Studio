
#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleReactive.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEDESIGNSTUDIO_API APuzzleReactive : public APuzzle
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void OnReceiveGreenSignal();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void OnReceiveRedSignal();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bANDSignalReceiver;
};
