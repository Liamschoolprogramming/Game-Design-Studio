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
#include "StructUtils/PropertyBag.h"
#include "VerseVM/VBPVMRuntimeType.h"


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
	
	
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(FName("TriggerSphere"));
	
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->SetGenerateOverlapEvents(true);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnSphereOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnSphereOverlapEnd);
	
	CameraAttachPoint = CreateDefaultSubobject<UCameraAttachPoint>(FName("CameraAttachPoint"));
	CameraAttachPoint->SetupAttachment(RootComponent);
	
}

void APlayerCharacter::AddInteractableObject(APuzzleInteractive* Object)
{
	ClosestInteractiveObjects.Remove(nullptr);
	
	if (Object)
	{
		ClosestInteractiveObjects.Add(Object);
	}
}

void APlayerCharacter::RemoveInteractableObject(APuzzleInteractive* Object)
{
	ClosestInteractiveObjects.Remove(nullptr);
	if (Object)
	{
		ClosestInteractiveObjects.Remove(Object);
	}
}

void APlayerCharacter::InteractWithClosestObject()
{
	if (ClosestInteractiveObjects.IsEmpty()) return;
	
	
	FVector PlayerPosition = GetActorLocation();
	const FPlayerStats PlayerStats = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager()->GetPlayerStats();
	
	TWeakObjectPtr<APuzzleInteractive> ClosestObject = nullptr;
	float ClosestDistance = PlayerStats.InteractRange;
	for (const TWeakObjectPtr<APuzzleInteractive>& Obj : ClosestInteractiveObjects)
	{
		
		if (Obj.IsValid())
		{
			
			float dist = FVector::Dist(PlayerPosition, Obj->GetActorLocation());
			if (dist < ClosestDistance)
			{
				ClosestDistance = dist;
				ClosestObject = Obj;
			}
		}
	}
	
	if (ClosestObject.IsValid())
	{
		
		
		//Debug::PrintToScreen(FString::Printf(TEXT("%s is interacting with %s"), *GetName(), *ClosestObject->GetName()), 10.0f, FColor::Cyan);
		//call BP first as some things need it first (big boulder)
		ClosestObject->OnInteract(this);
		//then try the Cpp file
		ClosestObject->Interact(this);
		
	}
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

	FTimerDelegate SafeTimerDelegate;
	SafeTimerDelegate.BindUFunction(this, FName("SaveLastLocation"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(SafeTimerDelegate);
	
}
//sorta dirty fix to keep the player from flying away by spam swapping
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	
	FVector End = GetActorLocation() + (-GetActorUpVector() * 5000.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);            // Ignore self
	float HalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		
	Params.bTraceComplex = true;             // Use complex collision if needed
	Params.bReturnPhysicalMaterial = false;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera,Params );
	if (bHit)
	{
		HalfHeight += HitResult.Location.Z;
		//Debug::PrintToScreen(HitResult.Location.Z);
	}
	SetActorLocation(FVector(Start.X, Start.Y, HalfHeight));
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
				//Debug::PrintToScreen(PossessableEntity->GetName(), 10.0f);
				PlayerController->AddPossessableEntity(PossessableEntity);
			}
			
		}
		else if (OtherActor->GetClass()->IsChildOf(APuzzleInteractive::StaticClass()))
		{
			APuzzleInteractive* Puzzle = Cast<APuzzleInteractive>(OtherActor);
			if (PlayerController && Puzzle)
			{
				//Debug::PrintToScreen(Puzzle->GetName(), 10.0f);
				AddInteractableObject(Puzzle);
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
				//Debug::PrintToScreen(PossessableEntity->GetName(), 10.0f, FColor::Red);
				PlayerController->RemovePossessableEntity(PossessableEntity);
			}
			
		}
		else if (OtherActor->GetClass()->IsChildOf(APuzzleInteractive::StaticClass()))
		{
			APuzzleInteractive* Puzzle = Cast<APuzzleInteractive>(OtherActor);
			if (PlayerController && Puzzle)
			{
				//Debug::PrintToScreen(Puzzle->GetName(), 10.0f, FColor::Red);
				RemoveInteractableObject(Puzzle);
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

void APlayerCharacter::SaveLastLocation()
{
	if (this->GetVelocity().Z == 0.0f)
	{
		SafeLocation = this->GetActorLocation();
	}
}

UCameraAttachPoint* APlayerCharacter::GetAttachPoint()
{
	return CameraAttachPoint;
}
