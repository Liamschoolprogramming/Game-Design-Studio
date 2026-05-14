// Fill out your copyright notice in the Description page of Project Settings.


#include "DropShadow.h"

// Sets default values for this component's properties
UDropShadow::UDropShadow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	DropShadowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("DropShadow"));
	
	
	
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(
		TEXT("/Game/GameDesignStudio/Effects/DropShadow/M_DropShadowDecal.M_DropShadowDecal")
	);
	if (MaterialObj.Succeeded())
	{
		DropShadowMaterial = MaterialObj.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(
		TEXT("/Engine/BasicShapes/Plane.Plane")
	);
	if (MeshObj.Succeeded())
	{
		DropShadowMesh = MeshObj.Object;
	}
	// ...
}


// Called when the game starts
void UDropShadow::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		return;
	}
	// ...
	if (DropShadowMeshComponent)
	{
		DropShadowMeshComponent->SetupAttachment(GetOwner()->GetRootComponent());
		DropShadowMeshComponent->SetWorldScale3D(DropShadowSize);
		DropShadowMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (DropShadowMaterial)
		{
			DropShadowMeshComponent->SetStaticMesh(DropShadowMesh);
		}
		
		if (DropShadowMaterial)
		{
			DropShadowMeshComponent->SetMaterial(0, DropShadowMaterial);
		}
	}
	
	
	
}


// Called every frame
void UDropShadow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, GetOwner());
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit;

	FVector TraceEnd = GetOwner()->GetActorLocation() + (FVector::DownVector * DropShadowDistCheck);
	
	FVector TraceStart = GetOwner()->GetActorLocation() + (FVector::UpVector * 100);
	
	GetWorld()->LineTraceSingleByChannel(RV_Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams);

	if (RV_Hit.bBlockingHit)
	{
		if (DropShadowMeshComponent)
		{
			DropShadowMeshComponent->SetWorldLocation(RV_Hit.Location + (FVector::UpVector * DropShadowGap));
		}
	}
}

