// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCamera.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	
	bool bSettingDestination = false;

	UPROPERTY(EditAnywhere, Category="Camera")
	TSubclassOf<ACustomCamera> CameraReferenceClass;

	UPROPERTY(BlueprintReadOnly, Category="Camera")
	ACustomCamera* CameraReference;
	
	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	APlayerControllerBase();

	/*
	 * BEGIN INPUT SECTION
	 */
	//IMC
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	//Zoom action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* ZoomAction;

	//Move Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;
	
	//Look Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;
	
	//Jump Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	//Set Destination click action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SetDestinationClickAction;
	
	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookGateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* ToggleLockCameraToPawnAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SelectAction;

	UFUNCTION(BlueprintCallable, Category="Input")
	void CheckControlDevice(FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	bool bUsingGamepad = false;
	
	void Zoom(const FInputActionValue& Value);
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	UNiagaraSystem* ParticleSystem;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float PawnMovementSpeed = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float PawnRotationSpeed = 8.f;
	
	FRotator PawnDesiredRotation;
	bool bPawnHasMovementInput = false;
	
	//Essentially a toggle for if we want to be able to move the pawn without always point and click
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bCanUseWASDToMovePawn = true;
	
	//MPC for camera cutout material
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UMaterialParameterCollection* CameraMPC;
	
	
	void StartClick(const FInputActionValue& Value);
	void StopClick(const FInputActionValue& Value);
	
	void LookGate(const FInputActionValue& Value);
	void LookGateStart();
	void LookGateStop();
	void ToggleLockCameraToPawn(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	

public:
	virtual void SetupInputComponent() override;
	
};
