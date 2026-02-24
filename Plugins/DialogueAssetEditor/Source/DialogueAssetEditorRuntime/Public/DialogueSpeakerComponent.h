// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DialogueSpeakerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class DIALOGUEASSETEDITORRUNTIME_API UDialogueSpeakerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDialogueSpeakerComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName SpeakerName = FName("Speaker");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UCameraComponent* SpeakerCamera = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	USpringArmComponent* SpeakerCameraBoom = nullptr;
	
	
	
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ActivateSpeakerCamera();
	
	
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void OnSpeakerCameraEnabled(const AActor* OldTarget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	

	

	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
