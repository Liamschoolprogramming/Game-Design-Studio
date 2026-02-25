// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "Macros.h"
#include "PossessableEntity.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"


DECLARE_DELEGATE_OneParam(FHardwareDelegate, FHardwareInputDeviceChanged);

//Get whether the player controller has been set to be able to move or not
bool APlayerControllerBase::GetCanMove()
{
	return bCanMove;
}

//Set the controller's ability to move it's possessed pawn (controlled through possessable entity)
void APlayerControllerBase::SetCanMove(bool CanMove)
{
	bCanMove = CanMove;
}

void APlayerControllerBase::Jump(const FInputActionValue& Value)
{
	//Get the pawn we are possessing, if it is a character we can just call Jump, if not, add custom jump logic
	ACharacter* OurCharacter = Cast<ACharacter>(GetPawn());
	if (OurCharacter)
	{
		OurCharacter->Jump();
		
	}
	
}

void APlayerControllerBase::StopJumping(const FInputActionValue& Value)
{
	//Get the pawn we are possessing, if it is a character we can just call Jump, if not, add custom jump logic
	ACharacter* OurCharacter = Cast<ACharacter>(GetPawn());
	if (OurCharacter)
	{
		OurCharacter->StopJumping();
	}
}

void APlayerControllerBase::UpdateMPC()
{
	
	//Set player pawn position in the MPC
	if (!GetPawn()) return;
	if (!CameraMPC) return;
	UMaterialParameterCollectionInstance* MPCInstance =
		GetWorld()->GetParameterCollectionInstance(CameraMPC);
	if (!MPCInstance) return;
	MPCInstance->SetVectorParameterValue(FName("PlayerLocation"), GetPawn()->GetActorLocation());
}
//This adds a possessable entity to our array only if the Entity given is not a null pointer or if it is already in it
void APlayerControllerBase::AddPossessableEntity(APossessableEntity* Entity)
{
	if (ClosestPossessableEntities.Find(Entity) != INDEX_NONE) return;
	if (Entity)
	{
		ClosestPossessableEntities.Add(Entity);
	}
}
//This removes a possessable entity from our array only if the Entity given is not a null pointer. 
void APlayerControllerBase::RemovePossessableEntity(APossessableEntity* Entity)
{
	
	
	if (Entity == GetPawn() && PlayerReference)
	{
		/*This bit was for switching back to player however we probably want to instead do nothing
		 *Entity->SetPossessed(false);
		Possess(PlayerReference);
		ClosestPossessableEntities.Remove(Entity);
		IndexForPossessables = -1;*/
		
	}
	else if (Entity)
	{
		ClosestPossessableEntities.Remove(Entity);
	}
}

bool APlayerControllerBase::CanWeCyclePossessableEntity(int IndexToCheck)
{
	if (ClosestPossessableEntities.IsEmpty()) return false;
	
	//Debug::PrintToScreen(IndexToCheck);
	
	if (IndexToCheck == -1)
	{
		
		return true;
	}
	else if (IndexToCheck >= 0)
	{
		if (!ClosestPossessableEntities.IsValidIndex(IndexToCheck)) return false;
		//if (!CameraReference->CanSeeObject(ClosestPossessableEntities[IndexToCheck])) return false;
		if (!Macros::CanActorSeeActor(PlayerReference, ClosestPossessableEntities[IndexToCheck])) return false;
		if (GetPawn()->GetClass()->IsChildOf(APossessableEntity::StaticClass()) &&
	GetPawn()->GetClass()->GetSuperClass() == APossessableEntity::StaticClass())
		{
			
			
			APossessableEntity* PossessableEntity = Cast<APossessableEntity>(GetPawn());
			
			
			if (ClosestPossessableEntities[IndexToCheck] != PossessableEntity)
			{
				
				return true;
			}
		}
		else
		{
			if (ClosestPossessableEntities[IndexToCheck] != nullptr)
			{
				return true;
			}
		}
		
	}
	return false;
}


void APlayerControllerBase::InteractWithClosestObject()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	
	if (PlayerCharacter)
	{
		PlayerCharacter->InteractWithClosestObject();
	}
}

//check if we can possess an entity
bool APlayerControllerBase::CanPossessEntity(APossessableEntity* entity)
{
	if (!ClosestPossessableEntities.Contains(entity)) return false;
	if (!PlayerReference) return false;
	//if (!CameraReference->CanSeeObject(entity)) return false;
	if (!Macros::CanActorSeeActor(PlayerReference, entity)) return false;
	if (GetPawn()->GetClass()->IsChildOf(APossessableEntity::StaticClass()) &&
GetPawn()->GetClass()->GetSuperClass() == APossessableEntity::StaticClass())
	{
		APossessableEntity* OurPawn = Cast<APossessableEntity>(GetPawn());
		if (entity != OurPawn)
		{
				
			return true;
		}
	}
	else
	{
		if (entity != nullptr)
		{
			return true;
		}
	
	}
	return false;
}

void APlayerControllerBase::StartClick(const FInputActionValue& Value)
{
	
}

void APlayerControllerBase::StopClick(const FInputActionValue& Value)
{
}

void APlayerControllerBase::StopMove(const FInputActionValue& Value)
{
	bIsMoving = false;
}


void APlayerControllerBase::CyclePossessionUp()
{
	CyclePossession();
}

void APlayerControllerBase::CyclePossessionDown()
{
	CyclePossession();
}

void APlayerControllerBase::SortClosestPossessableEntitiesByDistance()
{
	FVector ReferenceLocation = GetPawn()->GetActorLocation();
	
	ClosestPossessableEntities.Sort([&](const APossessableEntity& A, const APossessableEntity& B)
	{
		

	return FVector::DistSquared(A.GetActorLocation(), ReferenceLocation)
		 < FVector::DistSquared(B.GetActorLocation(), ReferenceLocation);
	});
	
}

void APlayerControllerBase::LookGate(const FInputActionValue& Value)
{
	
	
}

void APlayerControllerBase::LookGateStart()
{
	if (CameraReference)
	{
		CameraReference->AllowCameraRotation(true);
	}
}

void APlayerControllerBase::LookGateStop()
{
	if (CameraReference)
	{
		CameraReference->AllowCameraRotation(false);
	}
}


void APlayerControllerBase::ToggleLockCameraToPawn(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.4, FColor::Red, "ToggleLockCameraToPawn");
	if (CameraReference)
	{
		CameraReference->bLockCameraToCharacter = !(CameraReference->bLockCameraToCharacter);
		APawn* OurPawn = GetPawn();
		if (CameraReference->bLockCameraToCharacter && OurPawn)
		{
			CameraReference->PerspectiveZoomSpline->SetWorldRotation(OurPawn->GetActorRotation());
		}
		CameraReference->AllowCameraRotation(false);
	}
}

void APlayerControllerBase::Select(const FInputActionValue& Value)
{
	
	
}

void APlayerControllerBase::Zoom(const FInputActionValue& Value)
{
	if (CameraReference)
	{
		CameraReference->ZoomCamera(Value.Get<float>());
		
	}
}

void APlayerControllerBase::Look(const FInputActionValue& Value)
{
	if (CameraReference)
	{
		if (bUsingGamepad)
		{
			
			CameraReference->AllowCameraRotation(true);
			FVector2D ActionValue = Value.Get<FVector2D>();
			
			//just so we only do one or the other and not both
			if (FMath::Abs(ActionValue.X)  > FMath::Abs(ActionValue.Y))
			{
				CameraReference->RotateCamera(Value.Get<FVector2D>());
			}
			else if (FMath::Abs(ActionValue.X) < FMath::Abs(ActionValue.Y))
			{
				//compensation for direction and speed
				CameraReference->ZoomCamera(-Value.Get<FVector2D>().Y * ControllerSensitivity);
				
			}
			
		}
		else
		{
			CameraReference->RotateCamera(Value.Get<FVector2D>());
		}
		
		
	}
}

void APlayerControllerBase::Move(const FInputActionValue& Value)
{
	if (!bCanMove)
	{
		return;
	}
	//move the camera if we have a reference to it
	if (CameraReference)
	{
		if (CameraReference->bLockCameraToCharacter == false)
		{
			CameraReference->MoveCamera(Value.Get<FVector2D>());
		}
		else
		{
			//only move the pawn if we are using gamepad or override
			APawn* OurPawn = GetPawn();
			if ((OurPawn && bUsingGamepad) || (OurPawn && bCanUseWASDToMovePawn))
			{
				
				FVector2D ActionValue = Value.Get<FVector2D>();
				
				
				FVector pos = OurPawn->GetActorLocation();
				
				
				
				
				//Stop any move to commands as we would double in speed
				StopMovement();
				bIsMoving = true;
				
				
				
				FVector CameraForward = CameraReference->ForwardVector();
				
				FVector CameraRight = CameraReference->RightVector();
				FRotator CurrentRotation = OurPawn->GetActorRotation();
				

				
				CameraForward = CameraForward * ActionValue.Y;
				CameraRight = CameraRight * ActionValue.X;

				
				
				FVector DirForRotation = CameraForward + CameraRight;

				
				
				

				//Move
				FVector Dir = CameraForward + CameraRight;
				//Compensate so we don't slam into the ground
				Dir = Dir * FVector(1, 1, 0);
				
				Dir.Normalize();
				FVector DeltaMove = pos + (Dir * PawnMovementSpeed * GetWorld()->GetDeltaSeconds());
				PawnVelocity = Dir * PawnMovementSpeed;
				OurPawn->SetActorLocation(DeltaMove);
				
				//Smoothly rotate to new direction
				
				FRotator TargetRotation = DirForRotation.Rotation();
				
				FRotator SmoothRot = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), PawnRotationSpeed);
				
				
				OurPawn->SetActorRotation(SmoothRot);
				
			}
			
		}
		
	}
}


void APlayerControllerBase::PossessTargetPawn()
{
	CameraReference->SetActorRotation(TargetPawn->GetActorRotation());
	
	CameraReference->ResetCameraRotation(TargetPawn->GetActorRotation());
	APossessableEntity* PossessableEntity = Cast<APossessableEntity>(TargetPawn);
	if (PossessableEntity)
	{
		PossessableEntity->SetPossessed(true);
		UE_LOG(LogTemp, Warning, TEXT("Entity ptr: %p"), PossessableEntity);
		UE_LOG(LogTemp, Warning, TEXT("Niagara ptr: %p"), PossessableEntity ? PossessableEntity->PossessableIndicatorNiagaraComponent : nullptr);
		if (UNiagaraComponent* NS = PossessableEntity->PossessableIndicatorNiagaraComponent)
		{
			NS->Deactivate();
		}
		
	}
	Possess(TargetPawn);
	
	PossessionTimerHandle.Invalidate();
	
}

void APlayerControllerBase::CyclePossession()
{
	if (bPossessed && PlayerReference)
	{
		APossessableEntity* PossessableEntity = Cast<APossessableEntity>(GetPawn());
		PossessableEntity->SetPossessed(false);
		CameraReference->SetActorRotation(PlayerReference->GetActorRotation());
		CameraReference->ResetCameraRotation(PlayerReference->GetActorRotation());
		TargetPawn = nullptr;
		bPossessed = false;
		Possess(PlayerReference);
			
		PossessionTimerHandle.Invalidate();
	} 
	else if (!bPossessed)
	{
		if (FacingPossessable == nullptr) return;
		if (PossessionTimerHandle.IsValid()) return; // don't stack handle
		
		const FPlayerStats PlayerStats = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetPlayerStatManager()->GetPlayerStats();
		PlayerStats.MindPoints >= 5 ? CastTime = 3.f : 6.f;
		
		if (!Macros::CanActorSeeActor(PlayerReference, FacingPossessable)) 
		{
			FTimerDelegate CycleTimerDelegate;
			CycleTimerDelegate.BindUFunction(this, FName("CyclePossessionUp"));
			GetWorld()->GetTimerManager().SetTimerForNextTick(CycleTimerDelegate);
			return;
		}
		
		if (FacingPossessable != nullptr)
		{
			TargetPawn = FacingPossessable;
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("PossessTargetPawn"));
			GetWorld()->GetTimerManager().SetTimer(PossessionTimerHandle, TimerDelegate, CastTime, false);
			if (PossessionWidget)
			{
				UUserWidget* PossessTimeWidget = CreateWidget(this, PossessionWidget);
				PossessTimeWidget->AddToViewport();
			}
			bPossessed = true;
			StaticCast<APossessableEntity*>(TargetPawn)->OnPossessedStart();
		}
	}
}

void APlayerControllerBase::DoMove(float Right, float Forward)
{
}

void APlayerControllerBase::DoLook(float Yaw, float Pitch)
{
}

APlayerControllerBase::APlayerControllerBase()
{
	
		
		FHardwareDelegate HardwareDelegate;
	
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//spawn camera
	if (CameraReferenceClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		
		FVector _SpawnLocation = GetPawn()->GetActorLocation();
		
		FRotator _SpawnRotation = GetPawn()->GetActorRotation();
		
		PlayerReference = Cast<APlayerCharacter>(GetCharacter());
		
		
		APlayerCameraManager* pcm = PlayerCameraManager.Get();
		
		
		CameraReference = GetWorld()->SpawnActor<ACustomCamera>(ACustomCamera::StaticClass(), _SpawnLocation, _SpawnRotation, SpawnParams);
	
		
		
		SetViewTarget(CameraReference);
		if (pcm && CameraReference)
		{
			CameraReference->pitchMax = PlayerCameraManager.Get()->ViewPitchMax;
			CameraReference->pitchMin = PlayerCameraManager.Get()->ViewPitchMin;
		}
	}
	
	//set up input
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	
	bAutoManageActiveCameraTarget = false;
	
	
	//setup cursor 
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	
	
}

void APlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult Hit(ForceInit);
	
	FVector PlayerLocation = PlayerReference->GetActorLocation();
	FVector Forward = PlayerReference->GetActorForwardVector();
	FVector Start = FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
	FVector End =  FVector(Start.X +  (Forward.X * 2000.f), Start.Y + (Forward.Y * 2000.f), Start.Z);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(PlayerReference);
	
	bool bHitSomething = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, 50.f, ObjectTypesArray, false, IgnoredActors, EDrawDebugTrace::ForOneFrame, Hit, true);
	AActor* HitActor = Hit.GetActor();
	
	if (bHitSomething && HitActor != nullptr)
	{
		if (HitActor->GetClass()->IsChildOf(APossessableEntity::StaticClass()) && HitActor != FacingPossessable)
		{
			FacingPossessable = StaticCast<APossessableEntity*>(HitActor);
		}
	}
	else
	{
		FacingPossessable = nullptr;
	}
	
	
	UpdateMPC();
}

void APlayerControllerBase::CheckControlDevice(FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId)
{
	UInputDeviceSubsystem* InputDeviceSubsystem  = UInputDeviceSubsystem::Get();
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (InputDeviceSubsystem  && LocalPlayer)
	{
		
		FHardwareDeviceIdentifier  DeviceType = InputDeviceSubsystem->GetInputDeviceHardwareIdentifier (InputDeviceId);
	 
		if (DeviceType.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Gamepad");
			bUsingGamepad = true;
		}
		else if (DeviceType.PrimaryDeviceType == EHardwareDevicePrimaryType::KeyboardAndMouse)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Player is using Keyboard and Mouse");
			bUsingGamepad = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Player is using another device");
			bUsingGamepad = false;
		}
		
	}
}

//bind all input actions
void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ZoomAction)
		{
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Zoom);
		}
		
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopMove);
		}
		
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Look);
			GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red, "Look");
		}
		if (JumpAction)
		{
			
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerControllerBase::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopJumping);
		}
		if (SetDestinationClickAction)
		{
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APlayerControllerBase::StartClick);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APlayerControllerBase::StopClick);
		}
		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Look);
		}
		if (LookGateAction)
		{
			EnhancedInputComponent->BindAction(LookGateAction, ETriggerEvent::Started, this, &APlayerControllerBase::LookGateStart);
			EnhancedInputComponent->BindAction(LookGateAction, ETriggerEvent::Completed, this, &APlayerControllerBase::LookGateStop);
			
		}
		if (ToggleLockCameraToPawnAction)
		{
			EnhancedInputComponent->BindAction(ToggleLockCameraToPawnAction,ETriggerEvent::Completed, this, &APlayerControllerBase::ToggleLockCameraToPawn);
		}
		if (SelectAction)
		{
			EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Select);
		}
		
		if (CyclePossessionUpAction)
		{
			EnhancedInputComponent->BindAction(CyclePossessionUpAction, ETriggerEvent::Completed, this, &APlayerControllerBase::CyclePossessionUp);
		}
		if (CyclePossessionDownAction)
		{
			EnhancedInputComponent->BindAction(CyclePossessionDownAction, ETriggerEvent::Completed, this, &APlayerControllerBase::CyclePossessionDown);
		}
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerControllerBase::InteractWithClosestObject);
		}
		
	}
}
