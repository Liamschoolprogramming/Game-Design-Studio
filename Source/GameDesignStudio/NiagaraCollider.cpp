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

// Called every frame
void ANiagaraCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

