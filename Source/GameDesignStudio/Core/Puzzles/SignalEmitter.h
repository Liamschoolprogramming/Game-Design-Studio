#pragma once

#include "SignalEmitter.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USignalEmitter : public UInterface
{
	GENERATED_BODY()
};

class ISignalEmitter
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalEmitter)
	void EmitGreenSignal();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalEmitter)
	void EmitRedSignal();
};