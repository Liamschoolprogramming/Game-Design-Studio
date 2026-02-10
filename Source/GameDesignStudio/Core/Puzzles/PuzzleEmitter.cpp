

#include "PuzzleEmitter.h"
#include "PuzzleReceiver.h"


APuzzleEmitter::APuzzleEmitter()
{
	PuzzleActorType = EPuzzleActorType::SignalEmitter;
}

void APuzzleEmitter::EmitGreenSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveGreenSignal(ActorId);
	}
}

void APuzzleEmitter::EmitRedSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveRedSignal(ActorId);
	}
}
