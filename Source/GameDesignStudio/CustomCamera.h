// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float CameraMovementSpeed = 10;
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveCamera(FVector2D ActionValue);
	
	bool bLockCameraToCharacter = true;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
