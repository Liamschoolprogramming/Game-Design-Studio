// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MirrorGolem.generated.h"
#include "PossessableEntity.cpp"
#include "PossessableEntity.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"

DECLARE_DELEGATE(FOnPossessedDelegate);

UCLASS()
class GAMEDESIGNSTUDIO_API AMirrorGolem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMirrorGolem();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	APlayerControllerBase* PlayerController;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
protected:
	// Called when the game starts or when spawned
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