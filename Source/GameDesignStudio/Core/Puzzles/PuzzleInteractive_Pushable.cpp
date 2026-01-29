#include "PuzzleInteractive_Pushable.h"
#include "EditorCategoryUtils.h"

APuzzleInteractive_Pushable::APuzzleInteractive_Pushable()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractRange = 500;
}

void APuzzleInteractive_Pushable::Tick(float DeltaTime)
{
	
	if (bBeingPushed && PushingCharacter != nullptr)
	{
		this->SetActorLocation(PushingCharacter->GetActorLocation() + Offset);
	}
}

void APuzzleInteractive_Pushable::Interact(APlayerCharacter* PlayerCharacter)
{
	if (bBeingPushed)
	{
		bBeingPushed = false;
		PushingCharacter = nullptr;
	}
	else
	{
		if (IsInRange(PlayerCharacter))
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacting!"));
			}
			PushingCharacter = PlayerCharacter;
			bBeingPushed = true;
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