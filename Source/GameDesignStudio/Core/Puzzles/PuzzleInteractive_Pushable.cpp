#include "PuzzleInteractive_Pushable.h"
#include "EditorCategoryUtils.h"
#include "VectorTypes.h"

APuzzleInteractive_Pushable::APuzzleInteractive_Pushable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APuzzleInteractive_Pushable::Tick(float DeltaTime)
{
	
	if (bBeingPushed && PushingCharacter != nullptr)
	{
		this->SetActorLocation(PushingCharacter->GetActorLocation() + PushingCharacter->GetActorForwardVector() * 200);
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
			
			if (!bGolemPushableOnly || (bGolemPushableOnly && PlayerCharacter->PlayerCharacterType == EPlayerCharacterType::Golem))
			{
				PushingCharacter = PlayerCharacter;
				bBeingPushed = true;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("cant push!!"));
			}
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