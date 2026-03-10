#pragma once


#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Core/Puzzles/SaveStation.h"
#include "GameFramework/Actor.h"
#include "SaveStationManager.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API USaveStationManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ASaveStation* ActiveSaveStation;
	
	
};
