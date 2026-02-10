// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Puzzles/PuzzleKillzone.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Interfaces/IPluginManager.h"

// Sets default values
APuzzleKillzone::APuzzleKillzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleKillzone::BeginPlay()
{
	Super::BeginPlay();
	
	KillComponent = NewObject<UBoxComponent>(this,FName("KillComponent"));
	
	KillComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	KillComponent->SetupAttachment(RootComponent);
	KillComponent->SetGenerateOverlapEvents(true);
		
	KillComponent->RegisterComponent();
	
	KillComponent->SetBoxExtent(BoxSize);
		
	KillComponent->OnComponentBeginOverlap.AddDynamic(this, &APuzzleKillzone::OnBoxBeginOverlap);
}

void APuzzleKillzone::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter != nullptr && (PlayerCharacter->PlayerCharacterType == PlayerToKill || KillAnyPlayer))
		{
			PlayerCharacter->SetActorLocation(PlayerCharacter->SafeLocation);
		}
	}
}

// Called every frame
void APuzzleKillzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

