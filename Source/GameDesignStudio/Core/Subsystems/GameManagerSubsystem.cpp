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
	RegisterManager<UGearManager>();
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

UGearManager* UGameManagerSubsystem::GetGearManager() const
{
	if (const TObjectPtr<UGameManagerBase>* Found = Managers.Find(UGearManager::StaticClass()))
	{
		return Cast<UGearManager>(Found->Get());
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
void UGameManagerSubsystem::RegisterActorToManager(TSubclassOf<UGameManagerBase> ManagerClass, FGuid Id, const FPersistantActorValues& ActorValues)
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
		this->GetManager(Actor->OwningManager)->Snapshot(Actor->GetActorGuid(), Actor->ActorValues);
	}
}
