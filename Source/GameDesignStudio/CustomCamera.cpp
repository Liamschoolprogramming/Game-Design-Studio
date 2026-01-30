// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCamera.h"

#include "Macros.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACustomCamera::ACustomCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	ZoomOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ZoomOrigin"));
	
	ZoomOrigin->SetRelativeLocation(FVector(0, 0, 0));
	RootComponent = ZoomOrigin;
	
	//Setup camera boom
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->bDoCollisionTest = false;

	

	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	PerspectiveZoomSpline = CreateDefaultSubobject<USplineComponent>(TEXT("ZoomSpline"));
	PerspectiveZoomSpline->SetupAttachment(RootComponent);

	TopDownZoomSpline = CreateDefaultSubobject<USplineComponent>(TEXT("TopDownZoomSpline"));
	
	TopDownZoomSpline->SetupAttachment(RootComponent);
	

	
	
	

	//CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150;

	//Setup camera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	
	
}
void ACustomCamera::ZoomCamera(float Value)
{
	if (bLockCameraToCharacter)
	{
		float temp = ((ZoomSpeed) * Value) + ZoomPercent;
	
		ZoomPercent = UKismetMathLibrary::FClamp (temp,0,1 );
	
		SetCameraTransformAlongSpline(ZoomPercent);
		
	}
	
}

void ACustomCamera::ToggleCameraMode()
{
	bInTopDownMode = !bInTopDownMode;
	SetCameraTransformAlongSpline(ZoomPercent);
}

void ACustomCamera::MoveCamera(FVector2D ActionValue)
{
	FVector pos = GetActorLocation();
	float z = pos.Z;
	FVector f = GetActorForwardVector();
	FVector r = GetActorRightVector();
	f = f * ActionValue.Y * CameraMovementSpeed;
	r = r * ActionValue.X * CameraMovementSpeed;
	
	pos = pos + f + r;
	pos.Z = z;
	SetActorLocation(pos);
}

void ACustomCamera::RotateCamera(FVector2D ActionValue)
{
	if (bAllowRotation)
	{
		
		FRotator rot = PerspectiveZoomSpline->GetComponentRotation();
		rot.Yaw = rot.Yaw + (ActionValue.X * CameraRotationSpeed);
		//if we are following BG3 camera exactly they don't do this
		/*rot.Pitch = rot.Pitch + (-ActionValue.Y * CameraRotationSpeed);
		
		if (rot.Pitch > pitchMax)
		{
			rot.Pitch = pitchMax;
		}
		if (rot.Pitch < pitchMin)
		{
			rot.Pitch = pitchMin;
		}*/
		
		PerspectiveZoomSpline->SetWorldRotation(rot);
	}
}

void ACustomCamera::AllowCameraRotation(bool bValue)
{
	bAllowRotation = bValue;
}

void ACustomCamera::SetCameraTransformAlongSpline(float percent)
{
	ZoomPercent = percent;

	bool bShouldToggle = false;

	if (!bInTopDownMode && ZoomPercent >= 1)
	{
		ZoomPercent = ToPerspectiveThreshold;     // start at beginning of new spline but give a bit so we dont switch back instantly
		bShouldToggle = true;
	}
	else if (bInTopDownMode && ZoomPercent <= 0)
	{
		ZoomPercent = ToTopDownThreshold;     // end of other spline
		bShouldToggle = true;
	}

	if (bShouldToggle)
	{
		bInTopDownMode = !bInTopDownMode;
	}

	Debug::PrintToScreen(percent);
	
	//swap depending on the camera mode
	USplineComponent* SplineComponent = bInTopDownMode? TopDownZoomSpline : PerspectiveZoomSpline;
	if (SplineComponent)
	{

		CameraBoom->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(CameraBoom->GetComponentLocation(), SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World)));
	
		FVector pos = SplineComponent->GetLocationAtTime(percent,ESplineCoordinateSpace::World);
		CameraBoom->SetWorldLocation(pos);
	}
	
	
	
	

	
}

// Called when the game starts or when spawned
void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
	//Sorta magic numbers because the blueprint seems to only listen to values defined here.
	
	if (PerspectiveZoomSpline)
	{
		if (PerspectiveZoomSpline->GetNumberOfSplinePoints() == 2)
		{
			
			PerspectiveZoomSpline->SetLocationAtSplinePoint(1, FVector(-326, 0, 350), ESplineCoordinateSpace::Local, true);
			PerspectiveZoomSpline->SetLocationAtSplinePoint(0, FVector(0,0,0), ESplineCoordinateSpace::Local, true);
			
			//These values are not what you would think they should be. For some reason FRotator(x,y,z) on the spline turns into (y,z,x) rotation.
			PerspectiveZoomSpline->SetRotationAtSplinePoint(1,FRotator(89,0,0), ESplineCoordinateSpace::World, true);
			PerspectiveZoomSpline->SetRotationAtSplinePoint(0,FRotator(0,180,0), ESplineCoordinateSpace::World, true);
			
			SetCameraTransformAlongSpline(ZoomPercent);
		}
	}
	
	if (TopDownZoomSpline)
	{
		
		if (TopDownZoomSpline->GetNumberOfSplinePoints() == 2)
		{
			TopDownZoomSpline->SetLocationAtSplinePoint(1, FVector(-20, 0, 1400), ESplineCoordinateSpace::Local, true);
			TopDownZoomSpline->SetLocationAtSplinePoint(0, FVector(0,0,300), ESplineCoordinateSpace::Local, true);
		}
	}
}

// Called every frame
void ACustomCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bLockCameraToCharacter == true)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			RootComponent->SetWorldLocation(PlayerCharacter->GetActorLocation());
			
			SetCameraTransformAlongSpline(ZoomPercent);
		}
		
	}else
	{
		SetCameraTransformAlongSpline(ZoomPercent);
	}

}

