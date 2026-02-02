// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	
	//Initialize camera arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	//Setup camera arm 
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	
	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Setup camera
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//TODO should be moved to PlayerController.cpp
void APlayerCharacter::DoKnockback(float _power, AActor* origin)
{
	
	FVector locations;
	locations = this->GetActorLocation() - origin->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.X) // The message itself as an FString

	);
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.Y) // The message itself as an FString

	);
	GEngine->AddOnScreenDebugMessage(
		-1,         // Key for the message (use -1 for a new key each time, or a specific key to update an existing message)
		5.0f,       // Duration the message is displayed (in seconds)
		FColor::Yellow, // Color of the text
		FString::Printf(TEXT("%f locations x power"), locations.Z) // The message itself as an FString

	);
	locations *= FVector(1,1,0);
	
	locations = locations.GetSafeNormal(1.0);
	
	locations.Normalize(1.0);
	
	LaunchCharacter(locations * _power, false, false);
}

