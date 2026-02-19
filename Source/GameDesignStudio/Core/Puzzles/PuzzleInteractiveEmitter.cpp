
#include "PuzzleInteractiveEmitter.h"
#include "Core/Debug/DebugUtils.h"
#include "PuzzleReceiver.h"

APuzzleInteractiveEmitter::APuzzleInteractiveEmitter()
{
	PuzzleActorType = EPuzzleActorType::SignalEmitter;
}


void APuzzleInteractiveEmitter::SetActivatedState_Implementation(bool ActiveState) { }

void APuzzleInteractiveEmitter::EmitGreenSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveGreenSignal(ActorId);
	}
	SetActivatedState(true);
}

void APuzzleInteractiveEmitter::EmitRedSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveRedSignal(ActorId);
	}
	SetActivatedState(false);
}

void APuzzleInteractiveEmitter::Interact(APlayerCharacter* PlayerCharacter)
{
	EmitGreenSignal();
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(EmitSignalTimer);
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("EmitRedSignal"));
	TimerManager.SetTimer(EmitSignalTimer, TimerDelegate, EmitSignalTimerDuration, false);
}