// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACustomCamera::ACustomCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	//Setup camera boom
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->bDoCollisionTest = false;

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150;

	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Setup camera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
}

void ACustomCamera::MoveCamera(FVector2D ActionValue)
{
	FVector pos = GetActorLocation();
	FVector f = GetActorForwardVector();
	FVector r = GetActorRightVector();
	f = f * ActionValue.Y * CameraMovementSpeed;
	r = r * ActionValue.X * CameraMovementSpeed;
	
	pos = pos + f + r;
	SetActorLocation(pos);
}

// Called when the game starts or when spawned
void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
	
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
			SetActorLocation(PlayerCharacter->GetActorLocation());
		}
		
	}

}

