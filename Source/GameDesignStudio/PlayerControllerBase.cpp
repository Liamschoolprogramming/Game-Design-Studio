// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "Macros.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SplineComponent.h"

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
		if (!CameraReference->CanSeeObject(ClosestPossessableEntities[IndexToCheck])) return false;
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
	
	if (!CameraReference->CanSeeObject(entity)) return false;
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
	//Do the move to here instead of blueprints
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility,true, Hit);
	
	if (Hit.bBlockingHit && CameraReference->bLockCameraToCharacter == true && !bIsMoving)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
		if (ParticleSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ParticleSystem, Hit.Location);
		}
		
	}
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
	SortClosestPossessableEntitiesByDistance();
	if (IndexForPossessables + 1 >= ClosestPossessableEntities.Num())
	{
		
		IndexForPossessables = -1;
		
		
		
	}
	else
	{
		
		IndexForPossessables++;
	}
	
		CyclePossession();
}

void APlayerControllerBase::CyclePossessionDown()
{
	SortClosestPossessableEntitiesByDistance();
	bool bCanCycle = false;
	if (IndexForPossessables - 1 < -1)
	{
		if (CanWeCyclePossessableEntity(ClosestPossessableEntities.Num() - 1))
		{
			IndexForPossessables = ClosestPossessableEntities.Num()-1;
			bCanCycle = true;
		}
		
	}
	else
	{
		if (CanWeCyclePossessableEntity(IndexForPossessables - 1))
		{
			IndexForPossessables--;
			bCanCycle = true;
		}
		
	}
	if (bCanCycle)
	{
		CyclePossession();
	}
	
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
			
		}else
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

void APlayerControllerBase::CyclePossession()
{
	if (ClosestPossessableEntities.IsEmpty()) return;
	
	//Debug::PrintToScreen(IndexForPossessables);
	
	if (IndexForPossessables == -1)
	{
		
		
		APossessableEntity* PossessableEntity = Cast<APossessableEntity>(GetPawn());
		if (PossessableEntity && PlayerReference)
		{
			PossessableEntity->SetPossessed(false);
			CameraReference->SetActorRotation(PlayerReference->GetActorRotation());
			CameraReference->ResetCameraRotation(PlayerReference->GetActorRotation());
			Possess(PlayerReference);
			
			
			
		}
		
		
		
	}
	else if (IndexForPossessables >= 0)
	{
		if (!ClosestPossessableEntities.IsValidIndex(IndexForPossessables)) return;
		if (!CameraReference->CanSeeObject(ClosestPossessableEntities[IndexForPossessables]))
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("CyclePossessionUp"));
			GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
			return;
		}
		if (GetPawn()->GetClass()->IsChildOf(APossessableEntity::StaticClass()) &&
	GetPawn()->GetClass()->GetSuperClass() == APossessableEntity::StaticClass())
		{
			
			
			APossessableEntity* PossessableEntity = Cast<APossessableEntity>(GetPawn());
			if (PossessableEntity)
			{
				PossessableEntity->SetPossessed(false);
			}
			
			if (ClosestPossessableEntities[IndexForPossessables] != PossessableEntity)
			{
				
				ClosestPossessableEntities[IndexForPossessables]->SetPossessed(true);
				CameraReference->SetActorRotation(ClosestPossessableEntities[IndexForPossessables]->GetActorRotation());
				CameraReference->ResetCameraRotation(ClosestPossessableEntities[IndexForPossessables]->GetActorRotation());
				Possess(ClosestPossessableEntities[IndexForPossessables]);
				
			}
		}
		else
		{
			if (ClosestPossessableEntities[IndexForPossessables] != nullptr)
			{
				ClosestPossessableEntities[IndexForPossessables]->SetPossessed(true);
				CameraReference->SetActorRotation(ClosestPossessableEntities[IndexForPossessables]->GetActorRotation());
				CameraReference->ResetCameraRotation(ClosestPossessableEntities[IndexForPossessables]->GetActorRotation());
				Possess(ClosestPossessableEntities[IndexForPossessables]);
				
			}
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
