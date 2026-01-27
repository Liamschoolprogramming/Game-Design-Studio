// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize camera arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 800;

	//Setup camera arm attach to the root component of the class
	CameraBoom->SetupAttachment(RootComponent);

	//use the pawn control rotation
	CameraBoom->bUsePawnControlRotation = true;

	//Initialize Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Set attach to the camera boom
	FollowCamera->SetupAttachment(CameraBoom);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		//find which direction is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		//find which direction is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//bind move
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//bind look
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

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

