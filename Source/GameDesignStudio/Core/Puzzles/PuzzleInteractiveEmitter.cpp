// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleInteractiveEmitter.h"
#include "PuzzleReceiver.h"

APuzzleInteractiveEmitter::APuzzleInteractiveEmitter()
{
	PuzzleActorType = EPuzzleActorType::SignalEmitter;
}

void APuzzleInteractiveEmitter::EmitGreenSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveGreenSignal(ActorId);
	}
}

void APuzzleInteractiveEmitter::EmitRedSignal()
{
	if (LinkedReceiver != nullptr)
	{
		APuzzleReceiver* Receiver = static_cast<APuzzleReceiver*>(LinkedReceiver);
		Receiver->ReceiveRedSignal(ActorId);
	}
}

void APuzzleInteractiveEmitter::Interact(APlayerCharacter* PlayerCharacter)
{
	// reset timer if active
	// otherwise start timer
}