#pragma once

#include "Managers/PlayerStatManager.h"
#include "PlayerCharacterData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCharacterTypeIcon : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerCharacterType PlayerCharacterType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
	
	FPlayerCharacterTypeIcon()
	{
		PlayerCharacterType = EPlayerCharacterType::Default;
		Icon = nullptr;
	}
	
	FPlayerCharacterTypeIcon(EPlayerCharacterType CharacterType, TSoftObjectPtr<UTexture2D> CharacterIcon)
	{
		PlayerCharacterType = CharacterType;
		Icon = CharacterIcon;
	}
};