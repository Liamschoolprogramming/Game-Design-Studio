// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CppDoor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CppPressurePlate.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API ACppPressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppPressurePlate();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* PlateMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* SphereCollision;
	
	//Material when pressure plate is not being pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInterface* DefaultMaterial;
	
	//Material when pressure plate is being pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInterface* PressedMaterial;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnPressurePlatePressed(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPressurePlateReleased(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Config")
	ACppDoor* DoorRef;
};
