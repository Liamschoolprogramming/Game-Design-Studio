// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraCollider.h"

// Sets default values
ANiagaraCollider::ANiagaraCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	
	

}


// Called when the game starts or when spawned
void ANiagaraCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANiagaraCollider::SetSize(FVector StartPoint, FVector EndPoint)
{
	
	
	FVector Dir = EndPoint - StartPoint;
	float Dist = Dir.Size();
	FRotator Rot = (StartPoint - EndPoint).GetSafeNormal().Rotation();
	Rot.Pitch += 90.f;
	
	
	StaticMesh->SetWorldLocation((StartPoint));
	StaticMesh->SetWorldRotation(Rot);
	StaticMesh->SetWorldScale3D(FVector(4.f, 4.f, Dist / CapsuleHalfHeight));
	
}

// Called every frame
void ANiagaraCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

