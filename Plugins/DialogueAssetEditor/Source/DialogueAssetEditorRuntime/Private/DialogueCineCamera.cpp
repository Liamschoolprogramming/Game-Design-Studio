// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueCineCamera.h"

#include "DialogueMacros.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADialogueCineCamera::ADialogueCineCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AnimationPath = CreateDefaultSubobject<USplineComponent>("AnimationPath");
	AnimationPath->SetupAttachment(RootComponent);
	
	
}

void ADialogueCineCamera::StartAnimation()
{
	AnimationTime = 0;
	
	bStartAnimation = true;
}

void ADialogueCineCamera::ActivateCamera()
{


	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		OnCameraEnabled(PC->GetViewTarget());
		PC->SetViewTargetWithBlend(this, CameraTransitionTime);
		PC->StopMovement();
		SetAnimationAlongPath(0);
		
		DialogueMacros::CreateTimer( this, FName("StartAnimation"), CameraTransitionTime, false);
		
	}


}

void ADialogueCineCamera::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	InitializeCamera();
}

void ADialogueCineCamera::InitializeCamera()
{
	SetAnimationAlongPath(AnimationPreview/100.f);
}


void ADialogueCineCamera::SetAnimationAlongPath(const float Percent)
{
	
	
	if (AnimationPath)
	{
		const FVector Pos = AnimationPath->GetLocationAtTime(Percent,ESplineCoordinateSpace::World);
		const FRotator Rotation = AnimationPath->GetRotationAtTime(Percent,ESplineCoordinateSpace::World);
		
		// Convert to quat
		FQuat BaseQuat = Rotation.Quaternion();

		// Get the forward direction of that rotation
		FVector Forward = BaseQuat.GetUpVector();

		// Create offset around that forward axis
		FQuat OffsetQuat(Forward, FMath::DegreesToRadians(AnimationOffset));

		// Apply in local space
		FQuat FinalQuat = OffsetQuat * BaseQuat;

		FRotator FinalRot = FinalQuat.Rotator();
	
		//FRotator ResultRotator = ResultQuat.Rotator();
		GetCameraComponent()->SetWorldRotation(FinalRot);
		GetCameraComponent()->SetWorldLocation(Pos);
	}
	if (Percent > 1 )
	{
		bStartAnimation = false;
	}
}

// Called when the game starts or when spawned
void ADialogueCineCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueCineCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartAnimation)
	{
		SetAnimationAlongPath(AnimationTime);
		AnimationTime += (DeltaTime * AnimationSpeed)/100.f;
	}
}

