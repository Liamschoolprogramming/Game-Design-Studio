// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Managers/PlayerStatManager.h"
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
	
	
	//IMC
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prototype Variables")
	bool hasItem = false;
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	

	// i want this to be called in blueprints as well so im putting it here :)
	// this is so knockback can be done by anything and the code doesnt need to be rewritten like a thousand times
	UFUNCTION(BlueprintCallable)
	void DoKnockback(float Power, AActor* origin);


};


