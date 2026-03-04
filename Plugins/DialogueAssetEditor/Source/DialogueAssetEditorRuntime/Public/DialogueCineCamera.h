// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "DialogueCineCamera.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnFinishAnimation);
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API ADialogueCineCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogueCineCamera();

	FOnFinishAnimation OnFinishAnimation;
	
	UPROPERTY()
	USplineComponent* InternalAnimationPath;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USplineComponent* AnimationPath;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CameraSettings|Animation")
	FName CameraName;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CameraSettings|Animation")
	//Blend time when moving to this camera
	float CameraTransitionTime = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CameraSettings|Animation")
	//If we have a move animation for this camera (uses a spline)
	bool bHasAnimation = true;
	
	UFUNCTION(BlueprintCallable)
	void StartAnimation();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CameraSettings|Animation",meta = (EditCondition = "!bHasAnimation", EditConditionHides))
	//Used if bHasAnimation is false to determine how long we stay on this camera
	float CameraDuration = 1.f;
	
	float AnimationTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CameraSettings|Animation",meta = (EditCondition = "bHasAnimation", EditConditionHides))
	//How fast do we move along the line
	float AnimationSpeed = 50.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CameraSettings|Animation",meta = (EditCondition = "bHasAnimation", EditConditionHides))
	//Angle offset around the up axis as rotation for the camera
	float AnimationOffset = 90.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CameraSettings|Animation", meta = (ClampMin = "0", ClampMax = "100"),meta = (EditCondition = "bHasAnimation", EditConditionHides))
	//Percent along the path
	float AnimationPreview = 0.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CameraSettings|Animation",meta = (EditCondition = "bHasAnimation", EditConditionHides))
	//after the animation finishes, how long do we wait before moving on.
	float DelayAfterFinish = .1f;
	
	
	UFUNCTION(BlueprintCallable)
	void ActivateCamera();
	
#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
#endif
	
	
	void InitializeCamera();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	void OnCameraEnabled(const AActor* OldTarget);
	
	UFUNCTION()
	void EndAnimation();
	
	bool bStartAnimation = false;
	
	void SetAnimationAlongPath(float Percent);
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
