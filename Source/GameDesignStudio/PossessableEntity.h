// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PossessableEntity.generated.h"

DECLARE_DELEGATE(FOnPossessedDelegate);

UCLASS()
class GAMEDESIGNSTUDIO_API APossessableEntity : public ACharacter
{
	GENERATED_BODY()

public:
	APossessableEntity();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FOnPossessedDelegate OnPossessed;
	
	FOnPossessedDelegate GetOnPossessedDelegate()
	{
		return OnPossessed;
	}
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
