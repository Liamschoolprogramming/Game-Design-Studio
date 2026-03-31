// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleOwner.h"


// Sets default values
APuzzleOwner::APuzzleOwner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("PuzzleZone");
	if (BoxComponent)
	{
		RootComponent = BoxComponent;
	}
}

void APuzzleOwner::RegisterPuzzleActor(APuzzle* InPuzzle)
{
	if (InPuzzle)
	{
		if (!Puzzles.Find(InPuzzle))
		{
			InPuzzle->SetOwner(this);
			Puzzles.Add(InPuzzle);
			UE_LOG(LogTemp, Warning, TEXT("Puzzle %s Registered"), *InPuzzle->GetName());
		}
		
	}
}

void APuzzleOwner::OnOverlap( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("PlayerHitBox"))
	{
		bPlayerInPuzzle = true;
	}
}

void APuzzleOwner::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("PlayerHitBox"))
	{
		bPlayerInPuzzle = true;
	}
}

// Called when the game starts or when spawned
void APuzzleOwner::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APuzzleOwner::OnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APuzzleOwner::OnEndOverlap);
	TArray<AActor*> PuzzlesToCheck;
	BoxComponent->GetOverlappingActors(PuzzlesToCheck, APuzzle::StaticClass());
	for (AActor* Actor : PuzzlesToCheck)
	{
		if (Actor)
		{
			APuzzle* Puzzle = Cast<APuzzle>(Actor);
			if (Puzzle)
			{
				RegisterPuzzleActor(Puzzle);
			}
		}
	}
}

// Called every frame
void APuzzleOwner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

