// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerSubsystem.h"
#include "GameManagerBase.h"
#include "PuzzleRiverManager.h"
#include "Kismet/GameplayStatics.h"

void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
	//*******************************************************************************************//
	// RegisterManagers() method creates the object in memory based on the class, the range
	// for loop goes through that list and calls the objects initialize method after that.
	
	// The Initialize() can be though of an AActors BeginPlay() whatever you want to happen
	// as that object is being created should go in the Initialize() method.
	
	// Pair.Value is accessing the manager at the current index in the range
	// then we use the arrow operator to call the initialize method of that instance and
	// pass this subsytem as an argument so it registers with it.
	
	// Each UObject should only register with one subsystem, so each manager is registered to
	// the GameManagerSubsystem
	//*******************************************************************************************//
	
	Super::Initialize(Collection);
	
	UE_LOG(LogTemp, Warning, TEXT("GameManagerSubsystem Initialize: %s"), *UGameplayStatics::GetGameInstance(GetWorld())->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Registered GameManagerSubsystem")));
	
	RegisterManagers();
	
	//Initializing and Setting this subsystem to the owning subsystem of the manager
	for (auto& Pair : Managers)
	{
		Pair.Value->Initialize(this);
	}
	
}

void UGameManagerSubsystem::Deinitialize()
{
	for (auto& Pair : Managers)
	{
		Pair.Value->Shutdown();
	}
	
	Managers.Empty();
	
	Super::Deinitialize();
}

// Creating objects based on the class type used for the template and
// adding it to the managers array
void UGameManagerSubsystem::RegisterManagers()
{
	RegisterManager<UPuzzleRiverManager>();
}

template <typename T>
void UGameManagerSubsystem::RegisterManager()
{
	T* Manager = NewObject<T>(this);
	Managers.Add(T::StaticClass(), Manager);
}

UPuzzleRiverManager* UGameManagerSubsystem::GetPuzzleRiverManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UPuzzleRiverManager::StaticClass()))
	{
		return Cast<UPuzzleRiverManager>(Found->Get());
	}
	
	return nullptr;
}

UGameManagerBase* UGameManagerSubsystem::GetManager(TSubclassOf<UGameManagerBase> ManagerClass) const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(ManagerClass))
	{
		return Found->Get();
	}
	
	return nullptr;
}
