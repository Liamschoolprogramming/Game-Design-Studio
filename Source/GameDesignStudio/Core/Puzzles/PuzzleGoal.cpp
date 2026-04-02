// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Puzzles/PuzzleGoal.h"

APuzzleGoal::APuzzleGoal()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	if (BoxComponent)
	{
		RootComponent = BoxComponent;
		BoxComponent->ShapeColor = FColor(0, 255, 0);
	}
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APuzzleGoal::OnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APuzzleGoal::OnEndOverlap);
}

void APuzzleGoal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("PlayerHitBox"))
	{
		OnPuzzleSolved.Broadcast(true);
	}
}

void APuzzleGoal::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag("PlayerHitBox"))
	{
		
	}
}
