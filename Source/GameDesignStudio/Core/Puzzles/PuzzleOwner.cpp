// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleOwner.h"
#include "Core/Subsystems/PuzzleWorldSubsystem.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"
#if WITH_EDITOR
	#include "LevelEditorViewport.h"
#endif


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
		if (InPuzzle->bIsSolver)
		{
			SetNewSolver(InPuzzle);
		}
		Puzzles.AddUnique(InPuzzle);
		UE_LOG(LogTemp, Warning, TEXT("Puzzle %s Registered"), *InPuzzle->GetName());
		
		
	}
}

void APuzzleOwner::SetNewSolver(APuzzle* NewSolver)
{
	if (!NewSolver) return;
	
	if (Solver && Solver != NewSolver)
	{
		Solver->OnPuzzleSolved.RemoveDynamic(this, &APuzzleOwner::PuzzleSolved);
	}
	
	for (APuzzle* Puzzle : Puzzles)
	{
		if (Puzzle && Puzzle != NewSolver)
		{
			Puzzle->bIsSolver = false;
			
		}
	}
	Solver = NewSolver;
	if (!Solver->OnPuzzleSolved.IsAlreadyBound(this, &APuzzleOwner::PuzzleSolved))
	{
		Solver->OnPuzzleSolved.AddDynamic(this, &APuzzleOwner::PuzzleSolved);
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
		bPlayerInPuzzle = false;
	}
}

void APuzzleOwner::FaceTextToCamera()
{
	if (!TextRenderComponent) return;

#if WITH_EDITOR
	FVector CameraLocation;
	
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
	DebugUtils::LogToFile(this,"Solved: " + FString::Printf(TEXT("Puzzle %s: %s"),*PuzzleName.ToString(),*PuzzleState));
	bSolved = bIsSolved;
	OnSolved();
}

FPuzzleOwnerData APuzzleOwner::CaptureState() const
{
	FPuzzleOwnerData Result;
	Result.PuzzleName = PuzzleName;
	Result.bIsSolved = bSolved;
	UE_LOG(LogTemp,Warning, TEXT("Capture State %s, %s"), *PuzzleName.ToString(), bSolved ? TEXT("Solved") : TEXT("Not Solved"))
	DebugUtils::LogToFile(this,FString::Printf(TEXT("Capture State %s, %s"), *PuzzleName.ToString(), bSolved ? TEXT("Solved") : TEXT("Not Solved")));
	return Result;
}

void APuzzleOwner::RestoreState(const FPuzzleOwnerData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("RestoreState"))
	
	int32 Index = 0;
	for (auto Puzzle : Puzzles)
	{
		if (Puzzle)
		{
			FPersistantActorValues Values = *PuzzleDefaults.Find(Index);
			Puzzle->SetActorTransform(Values.ActorLocation);
			UE_LOG(LogTemp,Warning, TEXT("Reset Position %s"), *Puzzle->GetName())
			DebugUtils::LogToFile(this,FString::Printf(TEXT("Reset Position %s"), *Puzzle->GetName()));
		}
		Index ++;
	}
	
	if (PuzzleName == Data.PuzzleName)
	{
		UE_LOG(LogTemp,Warning, TEXT("FoundPuzzle %s"), *PuzzleName.ToString())
		bSolved = Data.bIsSolved;
		if (bSolved)
		{
			UE_LOG(LogTemp,Warning, TEXT("PuzzleWasSolved"))
			DebugUtils::LogToFile(this,FString::Printf( TEXT("PuzzleWasSolved")));
			DebugUtils::LogToFile(this,FString::Printf(TEXT("Puzzle count %i"), Puzzles.Num()));
			OnSolved();
		}
	}
	
}

// Called when the game starts or when spawned
void APuzzleOwner::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APuzzleOwner::OnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APuzzleOwner::OnEndOverlap);
	
	
	UPuzzleWorldSubsystem* PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	if (PuzzleWorldSubsystem)
	{
		PuzzleWorldSubsystem->RegisterPuzzleOwner(this);
	}
	
	GetPuzzles();
	
	if (!Puzzles.IsEmpty())
	{
		if (!Solver)
		{
			
			DebugUtils::LogToFile(this,"No solver");
			
#if WITH_EDITOR


			FString PuzzleString = TEXT("Puzzle ") + PuzzleName.ToString() + TEXT(" has no solver");
			
			FText Title = FText::FromString(PuzzleString);
			FText Message = FText::FromString(TEXT("No puzzle element in the bounds has bIsSolver equal to true. Either check the bounds or mark a puzzle element as the solver. Puzzle will not be marked as solved"));
			
			FMessageDialog::Open(EAppMsgType::Ok, Message, Title);
			
#endif
			
			
		}
		else
		{
			DebugUtils::LogToFile(this,"Solver found");
		}
	}
}

void APuzzleOwner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	TextRenderComponent->SetText(FText::FromName(PuzzleName));
	
#if WITH_EDITOR
	GetPuzzles();
	#endif
}
void APuzzleOwner::GetPuzzles()
{
	if (BoxComponent)
	{
		FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
		FVector BoxCenter = BoxComponent->GetComponentLocation();
		
		//Set puzzle elements in editor
		
		Puzzles.Empty();
		PuzzleDefaults.Empty();
		
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
		
		int32 Index = 0;
		for (FOverlapResult& Overlap : Overlaps)
		{
			APuzzle* Puzzle = Cast<APuzzle>(Overlap.GetActor());
			if (Puzzle)
			{
				PuzzleDefaults.Add(Index, Puzzle->ActorValues);
				UE_LOG(LogTemp, Warning, TEXT("Found Puzzle"));
				RegisterPuzzleActor(Puzzle);
				Index++;
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

