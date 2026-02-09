#pragma once

#include "SignalReceiver.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USignalReceiver : public UInterface
{
	GENERATED_BODY()
};

class ISignalReceiver
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void ReceiveGreenSignal();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=SignalReceiver)
	void ReceiveRedSignal();
};