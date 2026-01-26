// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
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
	
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UFUNCTION(BlueprintCallable)
		void OnPossess();
	
	UFUNCTION(BlueprintCallable)
		void OnCancelPossess();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Camera arm
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraBoom;

	//Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FollowCamera;


};
