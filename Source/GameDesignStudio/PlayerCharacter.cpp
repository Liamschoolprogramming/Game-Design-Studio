// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Macros.h"
#include "PossessableEntity.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"
#include  "PlayerControllerBase.h"


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
	
	GetCapsuleComponent()->ComponentTags.Add("PlayerHitBox");
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	
	
	
}



// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController =  Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController )
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
	
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SetSphereToPossessionRange"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
	

	
}

void APlayerCharacter::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		if (OtherActor->GetClass()->IsChildOf(APossessableEntity::StaticClass()))
		{
			APossessableEntity* PossessableEntity = Cast<APossessableEntity>(OtherActor);
			if (PlayerController && PossessableEntity && OtherComp->ComponentHasTag("HitBox"))
			{
				Debug::PrintToScreen(PossessableEntity->GetName(), 10.0f);
				PlayerController->AddPossessableEntity(PossessableEntity);
			}
			
		}
		else if (OtherActor->GetClass()->IsChildOf(APuzzleInteractive::StaticClass()))
		{
			APuzzleInteractive* Puzzle = Cast<APuzzleInteractive>(OtherActor);
			if (PlayerController && Puzzle)
			{
				Debug::PrintToScreen(Puzzle->GetName(), 10.0f);
				PlayerController->AddInteractableObject(Puzzle);
			}
		}
	}
}

void APlayerCharacter::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{

		if (OtherActor->GetClass()->IsChildOf(APossessableEntity::StaticClass()))
		{
			APossessableEntity* PossessableEntity = Cast<APossessableEntity>(OtherActor);
			if (PlayerController && PossessableEntity  && OtherComp->ComponentHasTag("HitBox"))
			{
				Debug::PrintToScreen(PossessableEntity->GetName(), 10.0f, FColor::Red);
				PlayerController->RemovePossessableEntity(PossessableEntity);
			}
			
		}
		else if (OtherActor->GetClass()->IsChildOf(APuzzleInteractive::StaticClass()))
		{
			APuzzleInteractive* Puzzle = Cast<APuzzleInteractive>(OtherActor);
			if (PlayerController && Puzzle)
			{
				Debug::PrintToScreen(Puzzle->GetName(), 10.0f, FColor::Red);
				PlayerController->RemoveInteractableObject(Puzzle);
			}
		}
		
	}
}


void APlayerCharacter::SetSphereToPossessionRange()
{
	if (!TriggerSphere) return;
	
	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	UGameManagerSubsystem* GMSub = GI->GetSubsystem<UGameManagerSubsystem>();
	if (!GMSub) return;

	UPlayerStatManager* PlayerStatManager = GMSub->GetPlayerStatManager();
	if (!PlayerStatManager) return;

	TriggerSphere->SetSphereRadius(PlayerStatManager->GetPlayerStats().PossessRange);

	
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
	
	locations *= FVector(1,1,0);
	
	locations = locations.GetSafeNormal(1.0);
	
	locations.Normalize(1.0);
	
	LaunchCharacter(locations * _power, false, false);
}

