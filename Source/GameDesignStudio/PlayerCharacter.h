// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Components/SphereComponent.h"

#include "Core/Subsystems/GameManagerSubsystem.h"
#include "Engine/TriggerSphere.h"
#include "Managers/PlayerStatManager.h"
#include "PlayerCharacter.generated.h"


class APuzzleInteractive;
class APlayerControllerBase;

UCLASS()
class GAMEDESIGNSTUDIO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UPROPERTY(BlueprintReadWrite)
	EPlayerCharacterType PlayerCharacterType = EPlayerCharacterType::Default;

	
	TSet<TWeakObjectPtr<APuzzleInteractive>> ClosestInteractiveObjects;
	
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void AddInteractableObject( APuzzleInteractive* Object);
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void RemoveInteractableObject(APuzzleInteractive* Object);

	
	
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void InteractWithClosestObject();	
	
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
	
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, 
							  AActor* OtherActor, 
							  UPrimitiveComponent* OtherComp, 
							  int32 OtherBodyIndex, 
							  bool bFromSweep, 
							  const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, 
							  AActor* OtherActor, 
							  UPrimitiveComponent* OtherComp, 
							  int32 OtherBodyIndex);
	
	USphereComponent* TriggerSphere;
	
	UFUNCTION()
	void SetSphereToPossessionRange();
	
	
	
	APlayerControllerBase* PlayerController;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prototype Variables")
	bool bIsInItemGate = false;
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	

	// i want this to be called in blueprints as well so im putting it here :)
	// this is so knockback can be done by anything and the code doesnt need to be rewritten like a thousand times
	UFUNCTION(BlueprintCallable)
	void DoKnockback(float Power, AActor* origin);


};


