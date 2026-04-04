// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"

#include "AutoSaveWarningController.h"
#include "DialogueSubsystem.h"
#include "GameManagerSubsystem.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Macros.h"
#include "PlayerControllerBase.h"
#include "PuzzleWorldSubsystem.h"
#include "SaveLoadIndicatorController.h"
#include "Core/ELSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("meta")), 0))
	{
		MetaSave = Cast<UMetaSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("meta")), 0));
		
	}else
	{
		MetaSave = Cast<UMetaSave>(UGameplayStatics::CreateSaveGameObject(UMetaSave::StaticClass()));
		
		if (MetaSave)
		{
			bool Success = UGameplayStatics::SaveGameToSlot(MetaSave,FString(TEXT("meta")), 0);
			if (Success)
			{
				
			}
			else
			{
				DEBUG_TO_SCREEN(FColor::Red,"Failed to save Settings");
			}
		}
		else
		{
			DEBUG_TO_SCREEN(FColor::Red,"Failed to create Settings");
		}
		
	}

	if (MetaSave)
	{
		AutoSaveFrequency = MetaSave->AutoSaveFrequency;
		MaxAutoSaves = MetaSave->MaxAutoSaves;
	}
	
	AutoSaveTimerDelegate.BindUFunction(this, FName("AutoSave"));
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, AutoSaveTimerDelegate, AutoSaveFrequency, true);
	
	
	
}

void USaveSubsystem::AutoSave()
{
	CreateSaveIndicator();
	SaveAllGameSubsystems(true);
	UE_LOG(LogTemp,Error,TEXT("AutoSave Saved"));
}

UELSSaveGame* USaveSubsystem::LoadGame(FString SlotName = "")
{
	if (SlotName.IsEmpty())
	{
		if (MetaSave)
		{
			UE_LOG(FSaveSubsystemLog, Warning, TEXT("Current save is %s"), *MetaSave->CurrentSave)
			if (UGameplayStatics::DoesSaveGameExist(MetaSave->CurrentSave, 0))
			{
				SaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaSave->CurrentSave, 0));
				return SaveGame;
			}else
			{
				UE_LOG(LogTemp,Error,TEXT("Can't load save. Tried to load slot %s"), *MetaSave->CurrentSave);
				return nullptr;
			}
		}
		else if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("meta")), 0))
		{
			MetaSave = Cast<UMetaSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("meta")), 0));
			if (MetaSave)
			{
					if (UGameplayStatics::DoesSaveGameExist(MetaSave->CurrentSave, 0))
				{
					SaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaSave->CurrentSave, 0));
					
					return SaveGame;
				}else
				{
					UE_LOG(LogTemp,Error,TEXT("Can't load save. Tried to load slot %s"), *MetaSave->CurrentSave);
					return nullptr;
				}
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("Slot name is empty and meta save failed to load"));
				return nullptr;
			}
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Slot name is empty and meta save failed to load"));
			return nullptr;
		}
	}
	else
	{
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			SaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
			MetaSave->CurrentSave = SlotName;
			SaveMeta();
			return SaveGame;
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Can't load save. Tried to load slot %s"), *SlotName);
			return nullptr;
		}
	}
}

void USaveSubsystem::DeleteSaveSlot(FString SlotName) const
{
	FString Path = FPaths::ProjectSavedDir() + "ScreenShots/" + SlotName + ".png";

	if (IFileManager::Get().FileExists(*Path))
	{
		IFileManager::Get().Delete(*Path);
	}
	
	if (MetaSave)
	{
		if (MetaSave->SaveSlotList.Contains(SlotName))
		{
			MetaSave->SaveSlotList.Remove(SlotName);
			UGameplayStatics::DeleteGameInSlot(SlotName, 0);
		}
		else if (MetaSave->AutoSaveKeys.Contains(SlotName))
		{
			MetaSave->AutoSaveKeys.Remove(SlotName);
		
			UGameplayStatics::DeleteGameInSlot(SlotName, 0);
		}
		
	}
}

void USaveSubsystem::CreateSaveGame()
{
	if (!SaveGame)
	{
		SaveGame = Cast<UELSSaveGame>(UGameplayStatics::CreateSaveGameObject(UELSSaveGame::StaticClass()));
		SaveGame->StartDate = FDateTime::UtcNow();
	}
}

/**
 * 
 * @param InTimeThreshold Time in seconds
 */
void USaveSubsystem::SetAutoSaveFrequency(float InTimeThreshold)
{
	if (InTimeThreshold == AutoSaveFrequency) return;
	if (!MetaSave) return;
	AutoSaveFrequency = InTimeThreshold;
	
	AutoSaveTimerDelegate.BindUFunction(this, FName("AutoSave"));
	MetaSave->AutoSaveFrequency = AutoSaveFrequency;
	SaveMeta();
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, AutoSaveTimerDelegate, AutoSaveFrequency, true);
}

void USaveSubsystem::SetMaxAutoSaves(int32 NewMax)
{
	MaxAutoSaves = NewMax;
	MetaSave->MaxAutoSaves = MaxAutoSaves;
	SaveMeta();
}

float USaveSubsystem::GetTimeTillAutoSave() const
{
	if (!GetWorld())
		return NAN;
	return GetWorld()->GetTimerManager().GetTimerRemaining(AutoSaveTimerHandle);
}

float USaveSubsystem::GetTimeElapsedSinceAutoSave() const
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(AutoSaveTimerHandle);
}

void USaveSubsystem::Deinitialize()
{
	
	Super::Deinitialize();
}

void USaveSubsystem::FindAllSubsystems()
{
	GameManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameManagerSubsystem>();
	Subsystems.Add(FName("GameManagerSubsystem"), GameManagerSubsystem);
	DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	Subsystems.Add(FName("DialogueSubsystem"), DialogueSubsystem);
}

bool USaveSubsystem::DoesSaveExist(const FString& SaveName)
{
	return UGameplayStatics::DoesSaveGameExist(SaveName, 0);
}

void USaveSubsystem::CreateSaveIndicator()
{
	if (!GetWorld()) return;
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UE_LOG(FSaveSubsystemLog, Warning, TEXT("Creating save indicator"))
		SaveIndicator =	USaveLoadIndicatorController::CreateInstance(PlayerController);
		SaveIndicator->AddToViewport();
	}
	
}

void USaveSubsystem::DestroySaveIndicator()
{
	if (SaveIndicator)
	{
		SaveIndicator->RemoveFromParent();
	}
	SaveIndicator = nullptr;
}

void USaveSubsystem::Save(const bool bInIsAutoSave, const FString& SlotName, const FString& SaveSlotPath)
{
	//get time
	const FDateTime Now = FDateTime::UtcNow();
	SaveGame->LastSaveDate = Now;

	//prepare the save data for subsystems
	FSaveData SaveData = PrepareSaveData();
	ConvertSaveData(SaveData);

	//specific values
	SaveGame->bIsAutoSave = bInIsAutoSave;
	SaveGame->World = GetWorld();
	SaveGame->SlotName = SlotName;
	if (!bInIsAutoSave)
	{
		MetaSave->SaveSlotList.Add(SlotName, Now);
	}
	MetaSave->CurrentSave = SlotName; 
	UE_LOG(FSaveSubsystemLog, Warning, TEXT("Saving to slot %s"), *SlotName)
	SavePlayer();
	SaveQuests();
	SavePuzzleWorld();
	CaptureToTexture(SaveSlotPath);
	SaveGame->ScreenshotPath = FPaths::ProjectSavedDir() + "ScreenShots/" + SaveSlotPath + ".png";
	UGameplayStatics::SaveGameToSlot(MetaSave,"meta", 0);
	UGameplayStatics::SaveGameToSlot(SaveGame,SaveSlotPath, 0);
}

void USaveSubsystem::SaveMeta()
{
	UGameplayStatics::SaveGameToSlot(MetaSave,"meta", 0);
}

void USaveSubsystem::SavePlayer()
{
	CreateSaveGame();
	if (SaveGame)
	{
		if (const APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController()))
		{
			SaveGame->PlayerLocation = PlayerController->PlayerReference->GetActorLocation();
			SaveGame->PlayerRotation = PlayerController->PlayerReference->GetActorRotation();
		}
	}
	
}

FPlayerData USaveSubsystem::LoadPlayer()
{
	FPlayerData PlayerData;
	 if (UELSSaveGame* Load = LoadGame())
	 {
	 	if (Load->World.Get() != GetWorld())
	 	{
	 		PlayerData.PlayerLocation = FVector(0, 0, 0);
	 		PlayerData.PlayerRotation = FRotator(-180,-180,-180);
	 		return PlayerData;
	 	}
		 PlayerData.PlayerLocation = LoadGame()->PlayerLocation;
	 	PlayerData.PlayerRotation = LoadGame()->PlayerRotation;
	 }
	else
	{
		PlayerData.PlayerLocation = FVector(0, 0, 0);
		PlayerData.PlayerRotation = FRotator(-180,-180,-180);
	}
	return PlayerData;
}

FSaveData USaveSubsystem::PrepareSaveData()
{
	FSaveData Data = FSaveData();
	if (!GameManagerSubsystem)
	{
		FindAllSubsystems();
	}
	
	UQuestManager* QuestManager = GameManagerSubsystem->GetQuestManager();
	if (QuestManager)
	{
		int FinishedQuests = 0;
		int TotalQuests = 0;
		for (auto Quest : QuestManager->Quests)
		{
			if (QuestManager->GetQuestState(Quest.Key) == EQuestState::COMPLETED)
			{
				FinishedQuests++;
			}
			TotalQuests++;
		}
		Data.QuestsComplete = FinishedQuests;
	}
	return Data;
}

/**
 * Make sure SaveGame exists before hand
 * @param SaveData Prepared from PrepareSaveData
 */
void USaveSubsystem::ConvertSaveData(const FSaveData& SaveData) const
{
	if (SaveGame)
	{
		SaveGame->QuestsComplete = SaveData.QuestsComplete;
		
	}
}

void USaveSubsystem::CaptureToTexture(const FString& SlotName)
{
	FString Path =FPaths::ProjectSavedDir() + "ScreenShots/" + SlotName + ".png";
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path),true);
	FScreenshotRequest::RequestScreenshot(Path, false,false);
	
}

UTexture2D* USaveSubsystem::LoadTexture2DFromFile(const FString& FilePath)
{
	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
		return nullptr;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num()))
		return nullptr;

	TArray<uint8> UncompressedData;
	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedData))
		return nullptr;

	UTexture2D* Texture = UTexture2D::CreateTransient(
		ImageWrapper->GetWidth(),
		ImageWrapper->GetHeight(),
		PF_B8G8R8A8
	);

	if (!Texture) return nullptr;

	void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, UncompressedData.GetData(), UncompressedData.Num());
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	Texture->UpdateResource();

	return Texture;
}


bool USaveSubsystem::SaveAllGameSubsystems(bool bIsAutoSave, FString SlotName, bool bOverride)
{
	OnSaveStart.Broadcast();
	
	//check if we are autosaving
	if (bIsAutoSave)
	{
		//check if metasave exists as thats where our slot info is
		if (MetaSave)
		{
			//if we are about to be above the max count, delete oldest and reindex
			if (MetaSave->AutoSaveKeys.Num()>= MaxAutoSaves)
			{
				UE_LOG(LogTemp,Error, TEXT("We are above max auto saves, deleting and reindexing"))
				FString OldestKey = MetaSave->AutoSaveKeys[0];
				//FDateTime OldestTimestamp = MetaSave->AutoSaveSlotList.FindAndRemoveChecked(OldestKey);
				//FString OldestFile = OldestKey + "_" + OldestTimestamp.ToString(TEXT("%Y_%m_%d__%H_%M_%S"));
				DeleteSaveSlot(OldestKey);
				
				
				TMap<FString, FDateTime> NewList;
				int count = 0;
				
				TArray<FString> NewKeys;

				for (int32 i = 0; i < MetaSave->AutoSaveKeys.Num(); i++)
				{
					FString OldSlotName = MetaSave->AutoSaveKeys[i];

					// Extract the timestamp suffix — everything after the first underscore
					FString Prefix, TimestampSuffix;
					OldSlotName.Split(TEXT("_"), &Prefix, &TimestampSuffix, ESearchCase::IgnoreCase, ESearchDir::FromStart);

					// Build the new slot name with the reindexed number
					FString NewSlotName = FString::Printf(TEXT("AutoSave%d_%s"), i, *TimestampSuffix);

					UELSSaveGame* OldSaveGame = nullptr;
					if (UGameplayStatics::DoesSaveGameExist(OldSlotName, 0))
					{
						OldSaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(OldSlotName, 0));
					}

					if (OldSaveGame)
					{
						UE_LOG(FSaveSubsystemLog, Warning, TEXT("Deleting and reindexing %s to %s"), *OldSlotName, *NewSlotName)
						UGameplayStatics::SaveGameToSlot(OldSaveGame, NewSlotName, 0);
						DeleteSaveSlot(OldSlotName);
					}

					NewKeys.Add(NewSlotName);
					UE_LOG(LogTemp, Warning, TEXT("Reindexed: %s -> %s"), *OldSlotName, *NewSlotName);
				}
				
				MetaSave->AutoSaveKeys = NewKeys;
			}
			
			//do the autosave
			const FDateTime Now = FDateTime::UtcNow();
			CreateSaveGame();
			UE_LOG(LogTemp,Warning, TEXT("Autosaving"))
			SaveGame->StartDate = Now;
			int NewIndex = MetaSave->AutoSaveKeys.Num();
			FString AutoSaveKey = TEXT("AutoSave") + FString::FromInt(NewIndex) + TEXT("_");
			
			
			

			FString FullSlotName = FString::Printf(TEXT("AutoSave%d_%s"), NewIndex, *FDateTime::Now().ToString(TEXT("%Y_%m_%d__%H_%M_%S")));
			MetaSave->AutoSaveKeys.Add(FullSlotName);
			SaveMeta();
			Save(true, FullSlotName, FullSlotName);
		}
	}
	else
	{
		//check if metasave exists as thats where our slot info is
		if (MetaSave)
		{
			//set date time to now if the slot is new or load the time.
			const FDateTime Now = FDateTime::UtcNow();
			if (!UGameplayStatics::DoesSaveGameExist(SlotName,0))
			{
				SaveGame = Cast<UELSSaveGame>(UGameplayStatics::CreateSaveGameObject(UELSSaveGame::StaticClass()));
				SaveGame->StartDate = Now;
			}
			else
			{
				if (!bOverride) return false;
				SaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
			}
			
			//save
			FString SaveSlotName = SlotName;

			Save(false, SlotName, SaveSlotName);
		
			
		}
	}
	//broadcast 
	OnSaveFinish.Broadcast();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("DestroySaveIndicator"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, true);
	return true;
}

TArray<UELSSaveGame*> USaveSubsystem::GetAllGameSaves() const
{
	TArray<UELSSaveGame*> GameSaves;
	UE_LOG(LogTemp,Warning, TEXT("GetAllGameSaves"))
	if (MetaSave)
	{
		for (auto AutoSaveSlot : MetaSave->AutoSaveKeys)
		{
			UE_LOG(LogTemp,Warning, TEXT("AutoSaveSlot: %s"), *AutoSaveSlot);
			if (UGameplayStatics::DoesSaveGameExist(AutoSaveSlot,0))
			{
				UELSSaveGame* Slot = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(AutoSaveSlot,0));
				if (Slot)
				{
					GameSaves.Add(Slot);
				}
			}
		}
		for (auto SaveSlot : MetaSave->SaveSlotList)
		{
			UE_LOG(LogTemp,Warning, TEXT("SaveSlot: %s"), *SaveSlot.Key);
			if (UGameplayStatics::DoesSaveGameExist(SaveSlot.Key,0))
			{
				UELSSaveGame* Slot = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot.Key,0));
				if (Slot)
				{
					GameSaves.Add(Slot);
				}
			}
		}
	}
	UE_LOG(LogTemp,Warning, TEXT("Length of saves: %i"), GameSaves.Num())
	return GameSaves;
}

void USaveSubsystem::SaveGameManager()
{
}

void USaveSubsystem::SavePuzzleWorld()
{

	UPuzzleWorldSubsystem* PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	if (PuzzleWorldSubsystem)
	{
		FPuzzleWorldData Data;
		Data.PuzzleOwners = PuzzleWorldSubsystem->CaptureAllStates();

		const FName LevelKey = FName(GetWorld()->GetOutermost()->GetFName());
		
		PuzzleWorldData.Add(LevelKey, Data);
		SaveGame->AllWorldData = PuzzleWorldData;
	}
	
	
	
}


void USaveSubsystem::LoadPuzzles()
{
	LoadGame();
	if (SaveGame)
	{
		PuzzleWorldData = SaveGame->AllWorldData;
		UE_LOG(LogTemp,Warning, TEXT("LoadPuzzles"))
		UPuzzleWorldSubsystem* PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
		if (PuzzleWorldSubsystem)
		{
			const FName LevelKey = FName(GetWorld()->GetOutermost()->GetFName());
			FPuzzleWorldData Data = *PuzzleWorldData.Find(LevelKey);
			PuzzleWorldSubsystem->RestoreAllStates(Data.PuzzleOwners);
			UE_LOG(LogTemp,Warning, TEXT("RestoredAllStates"))
		}
	}
	
}


void USaveSubsystem::SaveDialogue()
{
}

void USaveSubsystem::SaveQuests()
{
	CreateSaveGame();
	if (SaveGame)
	{
		UQuestManager* QuestManager = GameManagerSubsystem->GetQuestManager();
		if (QuestManager)
		{
			SaveGame->Quests = QuestManager->Quests;
		}
	}
}

bool USaveSubsystem::LoadQuests()
{
	if (LoadGame())
	{
		UQuestManager* QuestManager = GameManagerSubsystem->GetQuestManager();
		if (QuestManager)
		{
			QuestManager->Quests = LoadGame()->Quests;
			return true;
		}
	}
	return false;
}

void USaveSubsystem::Tick(float DeltaTime)
{
	if (!GetWorld())
	{
		return;
	}
	if (GetTimeTillAutoSave() < 60)
	{
		
		if (!HasNotifiedAutoSaveWarning)
		{
			UE_LOG(LogTemp,Warning, TEXT("Time till autosave less than a minute"))
			AutoSaveWarning.Broadcast();
			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				UE_LOG(FSaveSubsystemLog,Warning,TEXT("Creating Save Warning"))
				UAutoSaveWarningController* Controller = UAutoSaveWarningController::CreateInstance(PlayerController);
				Controller->AddToViewport();
				HasNotifiedAutoSaveWarning = true;
			}
			else
			{
				UE_LOG(LogTemp,Error, TEXT("No Player Controller"))
			}
			
		}
		
	}
	else
	{
		HasNotifiedAutoSaveWarning = false;
	}
}
