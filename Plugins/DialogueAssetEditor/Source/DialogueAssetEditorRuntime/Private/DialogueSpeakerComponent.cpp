// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSpeakerComponent.h"


#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueSpeakerComponentSub, Log, All);

// Sets default values for this component's properties
UDialogueSpeakerComponent::UDialogueSpeakerComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	SpeakerCamera = CreateDefaultSubobject<UCameraComponent>(FName("SpeakerCamera"));
	SpeakerCameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("SpeakerCameraBoom"));
	SpeakerCameraBoom->TargetArmLength = 100.f;
	
	SpeakerCamera->FieldOfView = 75.f;
	SpeakerCamera->PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	SpeakerCamera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	SpeakerCamera->PostProcessSettings.bOverride_DepthOfFieldSensorWidth = true;
	SpeakerCamera->PostProcessSettings.DepthOfFieldFocalDistance = 100.f;
	SpeakerCamera->PostProcessSettings.DepthOfFieldSensorWidth = 35.f;
	SpeakerCamera->PostProcessSettings.DepthOfFieldFstop = 2.8f;
	
	
}


void UDialogueSpeakerComponent::ActivateSpeakerCamera()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (PC)
	{
		OnSpeakerCameraEnabled(PC->GetViewTarget());
		PC->SetViewTargetWithBlend(this->GetOwner(), CameraTransitionTime);
		PC->StopMovement();
		
	}
	
}



// Called when the game starts
void UDialogueSpeakerComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UDialogueSpeakerComponent::OnRegister()
{
	Super::OnRegister();
	
	if (SpeakerCameraBoom)
	{
		SpeakerCameraBoom->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	if (SpeakerCamera)
	{
		SpeakerCamera->AttachToComponent(
			SpeakerCameraBoom,
			FAttachmentTransformRules::KeepRelativeTransform,
			USpringArmComponent::SocketName
		);
	}
	
	ComponentTags.Add(SpeakerName);
	
	
	
	
	
}


// Called every frame
void UDialogueSpeakerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

