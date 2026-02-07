// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCamera.h"

#include "DelayAction.h"
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
	
	float temp = ((ZoomSpeed) * Value) + ZoomPercent;

	ZoomPercent = UKismetMathLibrary::FClamp (temp,0,1 );

	SetCameraTransformAlongSpline(ZoomPercent);
		
		
	
	
}

void ACustomCamera::ToggleCameraMode()
{
	bInTopDownMode = !bInTopDownMode;
	SetCameraTransformAlongSpline(ZoomPercent);
}

float ACustomCamera::SetCameraHeight()
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (Pawn)
	{
		float PawnDesiredHeight = Pawn->GetActorLocation().Z;
		FVector Origin;
		FVector BoxExtent;
		Pawn->GetActorBounds(true,Origin, BoxExtent);
		float HalfHeight = BoxExtent.Z;
		FVector start = FVector(GetActorLocation().X, GetActorLocation().Y, PawnDesiredHeight + 2000);
		FVector end = FVector(GetActorLocation().X, GetActorLocation().Y, PawnDesiredHeight - HalfHeight);
		FHitResult HitResult;
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);            // Ignore self
		Params.AddIgnoredActor(Pawn);
		Params.bTraceComplex = true;             // Use complex collision if needed
		Params.bReturnPhysicalMaterial = false;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end, ECC_Camera,Params );
		if (bHit)
		{
			CameraHeight = HalfHeight + HitResult.Location.Z;
		}
		else
		{
			CameraHeight = PawnDesiredHeight;
		}
		
	}
	return CameraHeight;
	
}

void ACustomCamera::MoveCamera(FVector2D ActionValue)
{
	FVector pos = GetActorLocation();
	float z = pos.Z;
	
	FVector f = bInTopDownMode ? RootComponent->GetForwardVector(): CameraBoom->GetForwardVector();
	FVector r = bInTopDownMode ? RootComponent->GetRightVector(): CameraBoom->GetRightVector();
	f = f * ActionValue.Y * GetCameraSpeedFromDesiredDirection(ActionValue);
	r = r * ActionValue.X * GetCameraSpeedFromDesiredDirection(ActionValue);
	
	pos = pos + f + r;
	pos.Z = z;
	SetActorLocation(pos);
}

void ACustomCamera::RotateCamera(FVector2D ActionValue) const
{
	if (bAllowRotation)
	{
		
		FRotator rot = PerspectiveZoomSpline->GetComponentRotation();
		rot.Yaw = rot.Yaw + (ActionValue.X * CameraRotationSpeed);
		
		PerspectiveZoomSpline->SetWorldRotation(rot);
	}
}
//basically some fancy math to figure out which direction we are moving and whether we are reaching the edge of the camera bounds and smoothly slows us down if we move away from the pawn
float ACustomCamera::GetCameraSpeedFromDesiredDirection(FVector2D InputValue) const
{
	
	FVector f = bInTopDownMode ? RootComponent->GetForwardVector(): CameraBoom->GetForwardVector();
	FVector r = bInTopDownMode ? RootComponent->GetRightVector(): CameraBoom->GetRightVector();
	f = f * InputValue.Y;
	r = r * InputValue.X;
	FVector dir = f + r;
	dir.Normalize();
	APawn* OurPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OurPawn)
	{
		FVector DirToPawn = OurPawn->GetActorLocation() - GetActorLocation();
		float DistanceToPawn = DirToPawn.Length();
		DirToPawn.Normalize();
		
		float dot = FVector::DotProduct(dir, DirToPawn);
		dot = UKismetMathLibrary::FClamp(dot, 0.0f, 1.0f);
		
		float percentToDist = UKismetMathLibrary::NormalizeToRange(DistanceToPawn, MaxDistanceFromCharacter - SlowDownRange, MaxDistanceFromCharacter);
		percentToDist = UKismetMathLibrary::FClamp(percentToDist, 0.0f, 1.0f);
		
		float lerp = UKismetMathLibrary::Lerp(1,dot,percentToDist);
		lerp = lerp * DefaultCameraMovementSpeed * GetWorld()->GetDeltaSeconds();
		return lerp;
	}
	
	Debug::PrintToScreen("No pawn", 1, FColor::Red);
	return DefaultCameraMovementSpeed * GetWorld()->GetDeltaSeconds();
	
		
}

void ACustomCamera::AllowCameraRotation(bool bValue)
{
	bAllowRotation = bValue;
}

FVector ACustomCamera::ForwardVector() const
{
	//if we are in top down the forward should be relative to north and south
	if (bInTopDownMode)
	{
		return RootComponent->GetForwardVector();
	}
	
	return FollowCamera->GetForwardVector();
}

FVector ACustomCamera::RightVector() const
{
	//if we are in top down the Right should be relative to east and west
	if (bInTopDownMode)
	{
		return RootComponent->GetRightVector();
	}
	return FollowCamera->GetRightVector();
}


void ACustomCamera::SetupCameraLag() const
{
	//Wait to set position the first time before enabling the smoothing
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
}

void ACustomCamera::SetCameraTransformAlongSpline(float Percent)
{
	ZoomPercent = Percent;

	bool bShouldToggle = false;

	if (!bInTopDownMode && ZoomPercent >= 1)
	{
		ZoomPercent = ToPerspectiveThreshold;     // start at beginning of new spline but give a bit so we dont switch back instantly
		bShouldToggle = true;
	}
	else if (!bInTopDownMode && ZoomPercent <= ZoomMinPercent)
	{
		ZoomPercent = ZoomMinPercent;
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

	
	
	//swap depending on the camera mode
	USplineComponent* SplineComponent = bInTopDownMode? TopDownZoomSpline : PerspectiveZoomSpline;
	if (SplineComponent)
	{
		if (!bInTopDownMode)
		{
			CameraBoom->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(CameraBoom->GetComponentLocation(), RootComponent->GetComponentLocation()));
		}
		else
		{
			//We don't want to angle the camera while in top down and we can't have a camera pointing straight down so near -90 looks nice
			
			CameraBoom->SetWorldRotation(FRotator(-89.181545f,BasePawnRotation.Yaw,0.0f));
		}
		
	
		FVector pos = SplineComponent->GetLocationAtTime(Percent,ESplineCoordinateSpace::World);
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
			
			//These values are not what you would think they should be. Rotators in c++ seem to be y, z , x for Pitch, yaw, roll
			PerspectiveZoomSpline->SetRotationAtSplinePoint(1,FRotator(89,0,0), ESplineCoordinateSpace::Local, true);
			PerspectiveZoomSpline->SetRotationAtSplinePoint(0,FRotator(0,180,0), ESplineCoordinateSpace::Local, true);
			
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
	
	//Set position the first time
	if (bLockCameraToCharacter == true)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			
			RootComponent->SetWorldLocation(PlayerCharacter->GetActorLocation());
			RootComponent->SetWorldRotation(PlayerCharacter->GetActorRotation());
			BasePawnRotation = PlayerCharacter->GetActorRotation();
			Debug::PrintToScreen("We set the value");
			SetCameraTransformAlongSpline(ZoomPercent);
		}
		
	}
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SetupCameraLag"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
	
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
		float h = SetCameraHeight();
		RootComponent->SetWorldLocation(FVector(GetActorLocation().X,GetActorLocation().Y, h));
	}

}

