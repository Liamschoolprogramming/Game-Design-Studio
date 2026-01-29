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
	class USplineComponent* ZoomSpline;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float CameraMovementSpeed = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float CameraRotationSpeed = 10;
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveCamera(FVector2D ActionValue);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RotateCamera(FVector2D ActionValue);

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomSpeed = .1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	class USceneComponent* ZoomOrigin;

	UFUNCTION(BlueprintCallable, Category = "Zoom")
	void ZoomCamera(float Value);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomMinPercent = 0.4f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom")
	float ZoomPercent = ZoomMinPercent;
	float pitchMax;
	float pitchMin;
	void AllowCameraRotation(bool bValue);
	bool bAllowRotation = false;
	bool bLockCameraToCharacter = true;

	void SetCameraTransformAlongSpline(float percent);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

