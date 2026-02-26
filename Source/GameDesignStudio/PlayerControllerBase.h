// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCamera.h"

#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PossessableEntity.h"
#include "Core/Puzzles/PuzzleInteractive.h"
#include "PlayerControllerBase.generated.h"


class APlayerCharacter;
/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	bool GetCanMove();
	
	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool CanMove);
	
	bool bSettingDestination = false;

	UPROPERTY(EditAnywhere, Category="Camera")
	TSubclassOf<ACustomCamera> CameraReferenceClass;

	UPROPERTY(BlueprintReadOnly, Category="Camera")
	ACustomCamera* CameraReference;
	
	APlayerCharacter* PlayerReference;
	
	UFUNCTION(BlueprintCallable, Category="Possession")
	void PossessTargetPawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Possession")
	FTimerHandle PossessionTimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Possession")
	float CastTime = 6.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Possession")
	bool CanSwitchToOthersWhilePossessed = false;
	
	UPROPERTY(BlueprintReadOnly, Category="Possession")
	APawn* TargetPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Possession")
	TSubclassOf<UUserWidget> PossessionWidget;
	
	UFUNCTION(BlueprintNativeEvent, Category="Possession")
	void OnCyclePossession();
	
	// TODO REMOVE:
	void CyclePossession();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	float ControllerSensitivity = 0.2f;
	
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
	
	bool bIsMoving = false;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* CyclePossessionUpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* CyclePossessionDownAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* ConfirmPossessionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* InteractAction;
	
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
	
	UFUNCTION(BlueprintCallable, Category="Effects")
	void UpdateMPC();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float PawnMovementSpeed = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float PawnRotationSpeed = 8.f;
	
	FRotator PawnDesiredRotation;
	bool bPawnHasMovementInput = false;
	
	
	TArray<APossessableEntity*> ClosestPossessableEntities;
	
	
	void SortClosestPossessableEntitiesByDistance();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	FVector PawnVelocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Possession")
	int IndexForPossessables = -1; //-1 will be the index for the player character
	
	UFUNCTION(BlueprintCallable, Category="Possession")
	void AddPossessableEntity(APossessableEntity* Entity);
	
	UFUNCTION(BlueprintCallable, Category="Possession")
	void RemovePossessableEntity(APossessableEntity* Entity);

	bool CanWeCyclePossessableEntity(int IndexToCheck);

	
	
	//Essentially a toggle for if we want to be able to move the pawn without always point and click
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bCanUseWASDToMovePawn = true;
	
	//MPC for camera cutout material
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UMaterialParameterCollection* CameraMPC;
	
	
	UFUNCTION(BlueprintCallable, Category="Possession")
	bool CanPossessEntity(APossessableEntity* entity);
	
	void StartClick(const FInputActionValue& Value);
	void StopClick(const FInputActionValue& Value);
	
	void StopMove(const FInputActionValue& Value);

	void InteractWithClosestObject();
	
	UFUNCTION()
	void CyclePossessionUp();
	void CyclePossessionDown();
	void ConfirmPossession();
	
	void LookGate(const FInputActionValue& Value);
	void LookGateStart();
	void LookGateStop();
	void ToggleLockCameraToPawn(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//Whether the player is able to move or not (controlled by possessable entity for possessables that can't move
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool bCanMove = true;

private:
	

public:
	virtual void SetupInputComponent() override;
	
};



