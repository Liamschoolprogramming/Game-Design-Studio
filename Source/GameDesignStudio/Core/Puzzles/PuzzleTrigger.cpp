

#include "PuzzleTrigger.h"
#include "PuzzleReactive.h"


APuzzleTrigger::APuzzleTrigger()
{
	PuzzleActorType = EPuzzleActorType::SignalEmitter;
}

void APuzzleTrigger::EmitGreenSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReactive* Receiver = static_cast<APuzzleReactive*>(LinkedReceiver);
		Receiver->OnReceiveGreenSignal();
	}
}

void APuzzleTrigger::EmitRedSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReactive* Receiver = static_cast<APuzzleReactive*>(LinkedReceiver);
		Receiver->OnReceiveRedSignal();
	}
}
