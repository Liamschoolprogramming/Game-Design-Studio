// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Data/PlayerStats.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class GAMEDESIGNSTUDIO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(BlueprintReadWrite)
	EPlayerCharacterType PlayerCharacterType = EPlayerCharacterType::Default;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float CameraZoomSpeed = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float CameraZoomMin = 600;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float CameraZoomMax = 2000;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float CameraSensitivity = .5;
	
	//Camera arm
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;

	//Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FollowCamera;
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SetDestinationClickAction;
	
	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	//MPC for camera cutout material
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UMaterialParameterCollection* CameraMPC;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraCutoutCompensation = 100;
	
	bool bSettingDestination = false;

	void MoveForward(float AxisValue);
	void ClickStarted();
	void ClickEnded();
	void MoveRight(float AxisValue);
	
	void Zoom(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	
	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// i want this to be called in blueprints as well so im putting it here :)
	// this is so knockback can be done by anything and the code doesnt need to be rewritten like a thousand times
	UFUNCTION(BlueprintCallable)
	void DoKnockback(float Power, AActor* origin);


};


