// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DropShadow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GAMEDESIGNSTUDIO_API UDropShadow : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDropShadow();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	UStaticMeshComponent* DropShadowMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DropShadowDistCheck = 10000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DropShadowGap = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* DropShadowMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial* DropShadowMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector DropShadowSize = FVector(1.f,1.f,1.f);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
