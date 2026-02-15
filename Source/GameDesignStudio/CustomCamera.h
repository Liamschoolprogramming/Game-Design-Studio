// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "CustomCamera.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API ACustomCamera : public AActor
{
	GENERATED_BODY()
	//Camera arm
	
	
public:	
	// Sets default values for this actor's properties
	ACustomCamera();

	//Camera Boom
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;

	//Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USplineComponent* PerspectiveZoomSpline;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USplineComponent* TopDownZoomSpline;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	bool bInTopDownMode;
	
	const float ToTopDownThreshold = 0.8f;
	const float ToPerspectiveThreshold = 0.2f;
	
	const float TopDownAngle = -20.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Camera")
	bool CanSeeObject(AActor* Actor);

	
	void ToggleCameraMode();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float DefaultCameraMovementSpeed = 800;

	
	void ResetCameraRotation(const FRotator& NewRotation = FRotator::ZeroRotator);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float CameraRotationSpeed = 200;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MaxYawSpeed = 100;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float CameraHeight;

	float SetCameraHeight();
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveCamera(FVector2D ActionValue);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RotateCamera(FVector2D ActionValue) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	float GetCameraSpeedFromDesiredDirection(FVector2D InputValue) const;
	
	float MaxDistanceFromCharacter = 2600.0f;
	
	float SlowDownRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomSpeed = .1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	class USceneComponent* ZoomOrigin;

	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void ZoomCamera(float Value);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomMinPercent = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomPercent = ZoomMinPercent * 1.2;
	float pitchMax;
	float pitchMin;
	void AllowCameraRotation(bool bValue);
	bool bAllowRotation = false;
	bool bLockCameraToCharacter = true;
	
	FRotator BasePawnRotation;

	FVector ForwardVector() const;
	FVector RightVector() const;
	
	
	UFUNCTION(BlueprintInternalUseOnly)
	void SetupCameraLag() const;
	
	void SetCameraTransformAlongSpline(float Percent);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

