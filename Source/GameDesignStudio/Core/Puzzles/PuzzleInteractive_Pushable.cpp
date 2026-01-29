
#include "PuzzleInteractive_Pushable.h"
#include "EditorCategoryUtils.h"


APuzzleInteractive_Pushable::APuzzleInteractive_Pushable()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractRange = 500;
}

void APuzzleInteractive_Pushable::Tick(float DeltaTime)
{
	
	if (BeingPushed && PushingPawn != nullptr)
	{
		this->SetActorLocation(PushingPawn->GetActorLocation() + Offset);
	}
}

void APuzzleInteractive_Pushable::Interact(APawn* Pawn)
{
	if (BeingPushed)
	{
		BeingPushed = false;
		PushingPawn = nullptr;
	}
	else
	{
		if (IsInRange(Pawn))
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacting!"));
			}
			PushingPawn = Pawn;
			BeingPushed = true;
		}
		else
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Not in range!!"));
			}
		}
	}
}