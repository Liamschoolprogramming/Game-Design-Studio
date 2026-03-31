// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleOwner.generated.h"

UCLASS()
class GAMEDESIGNSTUDIO_API APuzzleOwner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleOwner();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<APuzzle*> Puzzles;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName PuzzleName;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bPlayerInPuzzle;

	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void RegisterPuzzleActor(APuzzle* InPuzzle);
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void OnOverlap( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
