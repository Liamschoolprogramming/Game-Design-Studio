// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"

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
	
	
	
	AutoSaveTimerDelegate.BindUFunction(this, FName("AutoSave"));
	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, AutoSaveTimerDelegate, AutoSaveFrequency, true);
	
}

void USaveSubsystem::AutoSave()
{
	SaveAllGameSubsystems(true);
	UE_LOG(LogTemp,Error,TEXT("AutoSave Saved"));
}

UELSSaveGame* USaveSubsystem::LoadGame(FString SlotName = "")
{
	if (SlotName.IsEmpty())
	{
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
		else if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("meta")), 0))
		{
			MetaSave = Cast<UMetaSave>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("meta")), 0));
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
	if (MetaSave)
	{
		if (MetaSave->SaveSlotList.Contains(SlotName))
		{
			MetaSave->SaveSlotList.Remove(SlotName);
			UGameplayStatics::DeleteGameInSlot(SlotName, 0);
		}
		else if (MetaSave->AutoSaveSlotList.Contains(SlotName))
		{
			FDateTime Time = MetaSave->AutoSaveSlotList.FindAndRemoveChecked(SlotName);
		
			UGameplayStatics::DeleteGameInSlot(SlotName + "_" + Time.ToString() , 0);
		}
		
	}
}

void USaveSubsystem::SetAutoSaveFrequency(float InTimeThreshold)
{
	if (InTimeThreshold == AutoSaveFrequency) return;
	AutoSaveFrequency = InTimeThreshold;
	
	AutoSaveTimerDelegate.BindUFunction(this, FName("AutoSave"));

	GetWorld()->GetTimerManager().SetTimer(AutoSaveTimerHandle, AutoSaveTimerDelegate, AutoSaveFrequency, true);
}

float USaveSubsystem::GetTimeTillAutoSave() const
{
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
   SaveIndicator =	USaveLoadIndicatorController::CreateInstance(GetWorld()->GetFirstPlayerController());
	SaveIndicator->AddToViewport();
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
	MetaSave->SaveSlotList.Add(SlotName, Now);
	MetaSave->CurrentSave = SlotName;
	SavePlayer();
			
	CaptureToTexture(SaveSlotPath);
	SaveGame->ScreenshotPath = FPaths::ProjectSavedDir() + "ScreenShots/" + SaveSlotPath + ".png";
	UGameplayStatics::SaveGameToSlot(MetaSave,"meta", 0);
	UGameplayStatics::SaveGameToSlot(SaveGame,SaveSlotPath, 0);
}

void USaveSubsystem::SaveMeta()
{
	UGameplayStatics::SaveGameToSlot(MetaSave,"meta", 0);
}

void USaveSubsystem::SavePlayer() const
{
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
	 if (LoadGame())
	 {
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
	UPlayerStatManager* PlayerStatManager = GameManagerSubsystem->GetPlayerStatManager();
	if (PlayerStatManager)
	{
		Data.MindStat = PlayerStatManager->GetPlayerStats().MindPoints;
		Data.StaminaStat = PlayerStatManager->GetPlayerStats().StaminaPoints;
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
		SaveGame->MindStat = SaveData.MindStat;
		SaveGame->StaminaStat = SaveData.StaminaStat;
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
	CreateSaveIndicator();
	if (bIsAutoSave)
	{
		
		if (MetaSave)
		{
			if (MetaSave->AutoSaveSlotList.Num() + 1 >= MaxAutoSaves)
			{
				UE_LOG(LogTemp,Error, TEXT("We are above max auto saves, deleting and reindexing"))
				FString OldestKey = MetaSave->AutoSaveKeys[0];
				FDateTime OldestTimestamp = MetaSave->AutoSaveSlotList.FindAndRemoveChecked(OldestKey);
				UGameplayStatics::DeleteGameInSlot(OldestKey + "_" + OldestTimestamp.ToString(), 0);
				MetaSave->AutoSaveKeys.Empty();
				TMap<FString, FDateTime> NewList;
				int count = 0;
				for (auto AutoSaveSlot : MetaSave->AutoSaveSlotList)
				{
					FString Number = AutoSaveSlot.Key;
					Number = Number.Replace(TEXT("AutoSave"),TEXT(""));
					Number = Number.Replace(TEXT("_"),TEXT(""));
					UELSSaveGame* OldSaveGame = nullptr;
					if (UGameplayStatics::DoesSaveGameExist(AutoSaveSlot.Key + "_" + AutoSaveSlot.Value.ToString(),0))
					{
						OldSaveGame = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(AutoSaveSlot.Key + "_" + AutoSaveSlot.Value.ToString(),0));
						
					}
					
					FString Key = AutoSaveSlot.Key;
					Key = Key.Replace(*Number,*FString::FromInt(count));
					NewList.Add(Key,AutoSaveSlot.Value);
					FString NewSlotName = Key + AutoSaveSlot.Value.ToString();
					if (OldSaveGame)
					{
						UGameplayStatics::SaveGameToSlot(OldSaveGame,NewSlotName,0);
						UGameplayStatics::DeleteGameInSlot(AutoSaveSlot.Key + "_" + AutoSaveSlot.Value.ToString(), 0);
					}
					MetaSave->AutoSaveKeys.Add(Key);
					UE_LOG(LogTemp,Warning, TEXT("New name %s"), *NewSlotName);
					count++;
				}
				MetaSave->AutoSaveSlotList = NewList;
			}
			const FDateTime Now = FDateTime::UtcNow();
			if (!SaveGame)
			{
				SaveGame = Cast<UELSSaveGame>(UGameplayStatics::CreateSaveGameObject(UELSSaveGame::StaticClass()));
				SaveGame->StartDate = Now;
			}
			UE_LOG(LogTemp,Warning, TEXT("Autosaving"))
			SaveGame->StartDate = Now;
			int NewIndex = MetaSave->AutoSaveKeys.Num();
			FString AutoSaveKey = TEXT("AutoSave") + FString::FromInt(NewIndex) + TEXT("_");
			MetaSave->AutoSaveSlotList.Add((AutoSaveKey), Now);
			MetaSave->AutoSaveKeys.Add(AutoSaveKey);
			FString SaveSlotName = AutoSaveKey + Now.ToString();

			Save(true, SlotName, SaveSlotName);
		}
	}
	else
	{
		if (MetaSave)
		{
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
			
			
			FString SaveSlotName = SlotName;

			Save(false, SlotName, SaveSlotName);
		
			
		}
	}
	OnSaveFinish.Broadcast();
	DestroySaveIndicator();
	return true;
}

TArray<UELSSaveGame*> USaveSubsystem::GetAllGameSaves() const
{
	TArray<UELSSaveGame*> GameSaves;
	UE_LOG(LogTemp,Warning, TEXT("GetAllGameSaves"))
	if (MetaSave)
	{
		for (auto AutoSaveSlot : MetaSave->AutoSaveSlotList)
		{
			UE_LOG(LogTemp,Warning, TEXT("AutoSaveSlot: %s"), *AutoSaveSlot.Key);
			if (UGameplayStatics::DoesSaveGameExist(AutoSaveSlot.Key + AutoSaveSlot.Value.ToString(),0))
			{
				UELSSaveGame* Slot = Cast<UELSSaveGame>(UGameplayStatics::LoadGameFromSlot(AutoSaveSlot.Key + AutoSaveSlot.Value.ToString(),0));
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
}

void USaveSubsystem::SaveDialogue()
{
}

void USaveSubsystem::SaveQuests()
{
}
