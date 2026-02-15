// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"



#include "GameFramework/Character.h"
#include "PossessableEntity.generated.h"

DECLARE_DELEGATE(FOnPossessedDelegate);

class APlayerControllerBase;

UCLASS()
class GAMEDESIGNSTUDIO_API APossessableEntity : public APlayerCharacter
{
	GENERATED_BODY()

public:
	APossessableEntity();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APlayerControllerBase* PlayerController;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	//Variable that can be set within a possessable entity BP that determines if it can move around or not
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanMove = true;
	
	UFUNCTION()
	void SetPossessed(bool NewPossessed);
	
protected:
	virtual void BeginPlay() override;
	
	bool bPossessed = false;
	bool bSettingDestination = false;
	
	UFUNCTION(BlueprintCallable)
	void OnTogglePossession();
	
	UFUNCTION(BlueprintCallable)
	void OnPossess();
	
	UFUNCTION(BlueprintCallable)
	void OnCancelPossess();
};
