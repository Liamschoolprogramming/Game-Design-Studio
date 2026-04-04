// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleOwner.h"

#include "LevelEditorViewport.h"
#include "Core/Subsystems/PuzzleWorldSubsystem.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APuzzleOwner::APuzzleOwner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("PuzzleZone");
	if (BoxComponent)
	{
		RootComponent = BoxComponent;
		BoxComponent->ShapeColor = FColor(0, 255, 255);
	}
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	if (TextRenderComponent)
	{
		TextRenderComponent->SetupAttachment(RootComponent);
		TextRenderComponent->SetAbsolute(false,false,true);
		TextRenderComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		TextRenderComponent->SetWorldSize(200);
		TextRenderComponent->bTickInEditor = true;
		TextRenderComponent->PrimaryComponentTick.bCanEverTick = true;
		TextRenderComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
		TextRenderComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
		
		FVector TextLocation = TextRenderComponent->GetRelativeLocation();
		TextLocation.Z = BoxComponent->GetScaledBoxExtent().Z + TextLocation.Z;
		TextRenderComponent->SetRelativeLocation(TextLocation);
		TextRenderComponent->bHiddenInGame = true;
		TextRenderComponent->SetVisibility(true);
		TextRenderComponent->Text = FText::FromName(PuzzleName);
	}
}

void APuzzleOwner::RegisterPuzzleActor(APuzzle* InPuzzle)
{
	if (InPuzzle)
	{
	
		InPuzzle->SetOwner(this);
		Puzzles.AddUnique(InPuzzle);
		UE_LOG(LogTemp, Warning, TEXT("Puzzle %s Registered"), *InPuzzle->GetName());
		
		
	}
}

void APuzzleOwner::SetNewSolver(APuzzle* NewSolver)
{
	if (!NewSolver) return;
	for (APuzzle* Puzzle : Puzzles)
	{
		if (Puzzle && Puzzle != NewSolver)
		{
			Puzzle->bIsSolver = false;
			
		}
	}
	Solver = NewSolver;
	Solver->OnPuzzleSolved.AddDynamic(this, &APuzzleOwner::PuzzleSolved);
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

void APuzzleOwner::FaceTextToCamera()
{
	if (!TextRenderComponent) return;
	
	FVector CameraLocation;
	

#if WITH_EDITOR
	if (!GetWorld()->IsGameWorld())
	{
		// Find the active editor viewport camera
		for (FLevelEditorViewportClient* ViewportClient : GEditor->GetLevelViewportClients())
		{
			if (ViewportClient && ViewportClient->IsPerspective())
			{
				CameraLocation = ViewportClient->GetViewLocation();
				break;
			}
		}
	}
	// Face toward camera (text renders facing -X by default)
	FVector ToCamera = (CameraLocation - TextRenderComponent->GetComponentLocation()).GetSafeNormal();
	FRotator LookAt = ToCamera.Rotation();
	TextRenderComponent->SetWorldRotation(LookAt);
#endif
}

void APuzzleOwner::PuzzleSolved(bool bIsSolved)
{
	FString PuzzleState = bIsSolved ? TEXT("Solved") : TEXT("Unsolved");
	UE_LOG(LogTemp, Warning, TEXT("Puzzle %s: %s"),*PuzzleName.ToString(),*PuzzleState);
	bSolved = bIsSolved;
	OnSolved();
}

FPuzzleOwnerData APuzzleOwner::CaptureState() const
{
	FPuzzleOwnerData Result;
	Result.PuzzleName = PuzzleName;
	Result.bIsSolved = bSolved;
	UE_LOG(LogTemp,Warning, TEXT("Capture State %s, %s"), *PuzzleName.ToString(), bSolved ? TEXT("Solved") : TEXT("Not Solved"))
	return Result;
}

void APuzzleOwner::RestoreState(const FPuzzleOwnerData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("RestoreState"))
	if (PuzzleName == Data.PuzzleName)
	{
		UE_LOG(LogTemp,Warning, TEXT("FoundPuzzle %s"), *PuzzleName.ToString())
		bSolved = Data.bIsSolved;
		if (bSolved)
		{
			UE_LOG(LogTemp,Warning, TEXT("PuzzleWasSolved"))
			OnSolved();
		}
	}
	int32 Index = 0;
	for (auto Puzzle : Puzzles)
	{
		if (Puzzle)
		{
			FPersistantActorValues Values = *PuzzleDefaults.Find(Index);
			Puzzle->SetActorTransform(Values.ActorLocation);
			UE_LOG(LogTemp,Warning, TEXT("Reset Position %s"), *Puzzle->GetName())
		}
		Index ++;
	}
}

// Called when the game starts or when spawned
void APuzzleOwner::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APuzzleOwner::OnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APuzzleOwner::OnEndOverlap);
	
	
	Puzzles.Empty();
	TArray<AActor*> PuzzlesToCheck;
	BoxComponent->GetOverlappingActors(PuzzlesToCheck, APuzzle::StaticClass());
	
	UPuzzleWorldSubsystem* PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	if (PuzzleWorldSubsystem)
	{
		PuzzleWorldSubsystem->RegisterPuzzleOwner(this);
	}
	
	int32 Index = 0;
	for (AActor* Actor : PuzzlesToCheck)
	{
		if (Actor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Actor"));
			APuzzle* Puzzle = Cast<APuzzle>(Actor);
			if (Puzzle)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Puzzle"));
				PuzzleDefaults.Add(Index,Puzzle->ActorValues);
				RegisterPuzzleActor(Puzzle);
				Index ++;
			}
		}
	}
	
	if (!Puzzles.IsEmpty())
	{
		if (!Solver)
		{
#if WITH_EDITOR


			FString PuzzleString = TEXT("Puzzle ") + PuzzleName.ToString() + TEXT(" has no solver");
			
			FText Title = FText::FromString(PuzzleString);
			FText Message = FText::FromString(TEXT("No puzzle element in the bounds has bIsSolver equal to true. Either check the bounds or mark a puzzle element as the solver. Puzzle will not be marked as solved"));
			
			FMessageDialog::Open(EAppMsgType::Ok, Message, Title);
			
#endif
			
			
		}
	}
}

void APuzzleOwner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	TextRenderComponent->SetText(FText::FromName(PuzzleName));
	
	
	GetPuzzles();
}
void APuzzleOwner::GetPuzzles()
{
	if (BoxComponent)
	{
		FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
		FVector BoxCenter = BoxComponent->GetComponentLocation();
		
		//Set puzzle elements in editor
		
		Puzzles.Empty();
		
		TArray<FOverlapResult> Overlaps;
		FCollisionShape CollisionBox = FCollisionShape::MakeBox(BoxExtent);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		GetWorld()->OverlapMultiByObjectType(
				Overlaps,
				BoxCenter,
				BoxComponent->GetComponentQuat(),
				FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
				CollisionBox,
				Params
			);

		for (FOverlapResult& Overlap : Overlaps)
		{
			APuzzle* Puzzle = Cast<APuzzle>(Overlap.GetActor());
			if (Puzzle)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Puzzle"));
				RegisterPuzzleActor(Puzzle);
			}
		}

	}
}

// Called every frame
void APuzzleOwner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FaceTextToCamera();
}

