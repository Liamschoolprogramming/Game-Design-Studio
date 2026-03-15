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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrentSaveStationIndex;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ASaveStation*> SaveStations;
	
	UFUNCTION(BlueprintCallable)
	void SetActiveSaveStation(ASaveStation* SaveStation);
	
	UFUNCTION(BlueprintCallable)
	void NextSaveStation();
	
	UFUNCTION(BlueprintCallable)
	void PreviousSaveStation();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ASaveStation*> GetSaveStations();
};
