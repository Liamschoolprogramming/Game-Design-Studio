
#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "PuzzleReceiver.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEDESIGNSTUDIO_API APuzzleReceiver : public APuzzle
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void ReceiveGreenSignal(FGuid EmitterId);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void ReceiveRedSignal(FGuid EmitterId);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"), Category=SignalReceiver)
	bool bANDSignalReceiver;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", InstanceEditable = "true"), Category=SignalReceiver)
	int RequiredGreenSignals;
};
