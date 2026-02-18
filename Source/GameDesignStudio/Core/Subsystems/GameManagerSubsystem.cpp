// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManagerSubsystem.h"
#include "PuzzleWorldSubsystem.h"
#include "Core/Debug/DebugUtils.h"
#include "Core/Managers/GameManagerBase.h"
#include "Managers/PuzzleRiverManager.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/MessageDialog.h"
#include "Managers/InventoryManager.h"
#include "Managers/PlayerStatManager.h"
#include "Managers/QuestManager.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

// RegisterManagers() method creates the object in memory based on the class, the range
// for loop goes through that list and calls the objects initialize method after that.
void UGameManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
	Super::Initialize(Collection);
	
	DEBUG_TO_SCREEN(FColor::Emerald, "GameManagerSubsystem Initialize: %s", *UGameplayStatics::GetGameInstance(GetWorld())->GetName());
	
	RegisterManagers();
	DEBUG_TO_SCREEN(FColor::Emerald, "Registered GameManagers");
	
	//Initializing and Setting this subsystem as the owning subsystem of the manager
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
	RegisterManager<UInventoryManager>();
	RegisterManager<UQuestManager>();
	RegisterManager<UPlayerStatManager>();
}

template <typename T>
void UGameManagerSubsystem::RegisterManager()
{
	T* Manager = NewObject<T>(this);
	Managers.Add(T::StaticClass(), Manager);
}

template <typename T>
T* UGameManagerSubsystem::GetManager()
{
	if (T* Manager = Cast<T>(UGameManagerBase::StaticClass()))
	{
		return Manager;
	}
	return nullptr;
}

UGameManagerBase* UGameManagerSubsystem::GetManagerByClass(TSubclassOf<UGameManagerBase> ManagerClass)
{
	UGameManagerBase* Manager = Managers.FindRef(ManagerClass);
	
	return Manager;
}

UPuzzleRiverManager* UGameManagerSubsystem::GetPuzzleRiverManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UPuzzleRiverManager::StaticClass()))
	{
		return Cast<UPuzzleRiverManager>(Found->Get());
	}
	
	return nullptr;
}

UInventoryManager* UGameManagerSubsystem::GetInventoryManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UInventoryManager::StaticClass()))
	{
		return Cast<UInventoryManager>(Found->Get());
	}
	
	return nullptr;
}

UQuestManager* UGameManagerSubsystem::GetQuestManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UQuestManager::StaticClass()))
	{
		return Cast<UQuestManager>(Found->Get());
	}
	
	return nullptr;
}

UPlayerStatManager* UGameManagerSubsystem::GetPlayerStatManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UPlayerStatManager::StaticClass()))
	{
		return Cast<UPlayerStatManager>(Found->Get());
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

// Defining type at runtime for registering actors to managers
void UGameManagerSubsystem::RegisterActorToManager(TSubclassOf<UGameManagerBase> ManagerClass, FName Id, const FPersistantActorValues& ActorValues)
{
	
	if (UGameManagerBase* Manager = GetManagerByClass(ManagerClass))
	{
		Manager->RegisterActor(Id, ActorValues);
		UE_LOG(LogTemp, Warning, TEXT("Registering Actor"));
	}
	
}

void UGameManagerSubsystem::SnapshotActorValues(APuzzle* Actor)
{
	FString ActorName = FString::Printf(TEXT("%s needs to have their owning manager set"), *Actor->GetName());
	
	// Called on every actor on it's beginplay
	if (Actor->OwningManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Snapshot Actor is nullptr"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(ActorName));
		
		// Editor calls really shouldn't be put in runtime code but for now it's fine
		#if WITH_EDITOR
		GEditor->RequestEndPlayMap();
		#endif
	}
	
	else if (Actor->OwningManager != nullptr)
	{
		this->GetManager(Actor->OwningManager)->Snapshot(Actor->ActorId, Actor->ActorValues);
	}
}

void UGameManagerSubsystem::LoadActor(TSubclassOf<UGameManagerBase> ManagerClass, FName Id, const FPersistantActorValues& ActorValues)
{	
	// This should be a call to the manager. The manager should have a method called LoadActorsFromSnapshot that calls
	// this from the level manager. It should then loop through it and matches the keys and then take that reference
	// dereference it and call a method called ApplySnapshot that is a private method. The method ApplySnapshot should
	// have a list of calls like applytransform or set actors state
	
	// This should happen on the manager, if the actor takes that data it breaks the one source of truth design pattern
	// where it is aware of why it needs to be applying all these stats to itself. The actor shouldn't manually apply these
	// states to itself. It will also be helpful so that if there is an actor that needs to also apply state but isn't a puzzle
	// actor, the system can just add another map of that type and either make a runtime cast or template method to handle
	// varrying types
	TMap<FName, TWeakObjectPtr<APuzzle>>& Actors = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>()->GetRuntimeActors();
}
