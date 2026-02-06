// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core/Managers/GameManagerBase.h"
#include "PlayerStatManager.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PossessRange;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double InteractRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HealthPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double StaminaPoints;
	
	// Mind Points corresponds to meters of Possession Range
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MindPoints;
	
	FPlayerStats()
	{
		PossessRange = 500.0;
		InteractRange = 500.0;
		HealthPoints = 3.0;
		StaminaPoints = 100.0;
		MindPoints = 10.0;
	}
};

UENUM(Blueprintable)
enum class EPlayerBoostableStat : uint8
{
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Mind UMETA(DisplayName = "Mind"),
};

UENUM(Blueprintable)
enum class EPlayerCharacterType : uint8
{
	Default UMETA(DisplayName = "Default"),
	Golem UMETA(DisplayName = "Golem"),
};

UCLASS()
class GAMEDESIGNSTUDIO_API UPlayerStatManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UFUNCTION(BlueprintCallable)
	void BoostPlayerStat(EPlayerBoostableStat StatToBoost, double Amount);
	
	UFUNCTION(BlueprintCallable)
	FPlayerStats GetPlayerStats();

protected:
	FPlayerStats PlayerStats;
};

