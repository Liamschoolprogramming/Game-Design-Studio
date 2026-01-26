// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppDoor.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API ACppDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppDoor();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* DoorMesh;
	
	//Material to use when door is open
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterial* OpenMaterial;
	
	//Material to use when door is closed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterial* ClosedMaterial;
	
	//Current state of the door
	bool bOpen;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void CloseDoor();
};
