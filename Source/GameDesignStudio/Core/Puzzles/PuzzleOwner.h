// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Data/PuzzleOwnerData.h"
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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTextRenderComponent* TextRenderComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<APuzzle*> Puzzles;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bSolved;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName PuzzleName;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bPlayerInPuzzle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APuzzle* Solver;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void RegisterPuzzleActor(APuzzle* InPuzzle);
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void SetNewSolver(APuzzle* NewSolver);
	
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
	
	void FaceTextToCamera();
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void PuzzleSolved(bool bIsSolved);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnSolved();
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	FPuzzleOwnerData CaptureState() const;
	
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void RestoreState(const FPuzzleOwnerData& Data);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
#if WITH_EDITOR
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }
#endif
	
	void GetPuzzles();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	TMap<int32,FPersistantActorValues> PuzzleDefaults;
};


