// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessableEntity.h"
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APossessableEntity::APossessableEntity()
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

// Called when the game starts or when spawned
void APossessableEntity::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

// Called every frame
void APossessableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APossessableEntity::OnPossess()
{
	PlayerController->Possess(this);
}

void APossessableEntity::OnCancelPossess()
{
	PlayerController->Possess(PlayerCharacter);
}

void APossessableEntity::MoveForward(float AxisValue)
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

void APossessableEntity::MoveRight(float AxisValue)
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

// Called to bind functionality to input
void APossessableEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//bind move
	PlayerInputComponent->BindAxis("MoveForward", this, &APossessableEntity::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APossessableEntity::MoveRight);

	//bind look
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("CancelPossess", IE_Pressed, this, &APossessableEntity::OnCancelPossess);
}
