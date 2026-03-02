#pragma once

#include "Managers/PlayerStatManager.h"
#include "PlayerCharacterData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCharacterTypeIcon
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerCharacterType PlayerCharacterType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	
	FPlayerCharacterTypeIcon()
	{
		PlayerCharacterType = EPlayerCharacterType::Default;
		Icon = nullptr;
	}
	
	FPlayerCharacterTypeIcon(EPlayerCharacterType CharacterType, UTexture2D* CharacterIcon)
	{
		PlayerCharacterType = CharacterType;
		Icon = CharacterIcon;
	}
};