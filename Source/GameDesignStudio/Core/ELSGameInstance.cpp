// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ELSGameInstance.h"

#include "DialogueSubsystem.h"
#include "Components/AudioComponent.h"
#include "Debug/DebugUtils.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/PuzzleRiverManager.h"
#include "Puzzles/Puzzle.h"
#include "Subsystems/PuzzleWorldSubsystem.h"
#include "Subsystems/SaveSubsystem.h"

void UELSGameInstance::PlayMusic(USoundBase* Music, float InFadeOutTimeOld, float InFadeInTimeNew)
{
	CurrentMusic = Music;
	FadeOutTimeOld = InFadeOutTimeOld;
	FadeInTimeNew = InFadeInTimeNew;

	if (ActiveMusicPlayer)
	{
		if (ActiveMusicPlayer->Sound != CurrentMusic)
		{
			StopMusic(FadeOutTimeOld);

			//fade in new
			ActiveMusicPlayer = UGameplayStatics::SpawnSound2D(this,CurrentMusic, 1.0f, 1.0f,0.0f,nullptr,true);
			if (ActiveMusicPlayer)
			{
				DEBUG_TO_SCREEN(FColor::Purple, "The audio was crossfaded");
				ActiveMusicPlayer->bAutoDestroy = false; // Prevent auto-delete
				ActiveMusicPlayer->FadeIn(FadeInTimeNew);
			}
			
		}
	}
	else
	{
		//fade in new
		ActiveMusicPlayer = UGameplayStatics::SpawnSound2D(this,CurrentMusic, 1.0f, 1.0f,0.0f,nullptr,true);
		
		if (ActiveMusicPlayer)
		{
			DEBUG_TO_SCREEN(FColor::Purple, "The audio was created");
			ActiveMusicPlayer->bAutoDestroy = false; // Prevent auto-delete
			ActiveMusicPlayer->FadeIn(FadeInTimeNew);
		}
	}
}

void UELSGameInstance::StopMusic(float FadeOutTime)
{
	if (ActiveMusicPlayer)
	{
		FadeOutMusicPlayer = ActiveMusicPlayer;
		FadeOutMusicPlayer->FadeOut(FadeOutTime, 0.f);
	}
	
}

void UELSGameInstance::SaveAudioSettings(float MusicVolumeIn, float SFXVolumeIn, float MasterVolumeIn, float DialogueVolumeIn)
{
	if (SettingsSaveGame)
	{
		SettingsSaveGame->MusicVolume = MusicVolumeIn;
		SettingsSaveGame->SFXVolume = SFXVolumeIn;
		SettingsSaveGame->DialogueVolume = DialogueVolumeIn;
		SettingsSaveGame->MasterVolume = MasterVolumeIn;

		if (MasterSoundMix && MusicSoundClass && SFXSoundClass && MasterSoundClass && DialogueSoundClass)
		{
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MasterSoundClass, MasterVolumeIn, 1,0,true);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MusicSoundClass,MusicVolumeIn, 1,0,true);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,SFXSoundClass,SFXVolumeIn, 1,0,true);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,DialogueSoundClass,DialogueVolumeIn, 1,0,true);
			UGameplayStatics::SaveGameToSlot(SettingsSaveGame,FString(TEXT("settings")), 0);
			UGameplayStatics::PushSoundMixModifier(GetWorld(),MasterSoundMix);
		}
		
	}
}

void UELSGameInstance::LoadAudioSettings()
{
	if (SettingsSaveGame)
	{

		
		float MasterVolumeIn = SettingsSaveGame->MasterVolume;
		float MusicVolumeIn = SettingsSaveGame->MusicVolume;
		float SFXVolumeIn = SettingsSaveGame->SFXVolume;
		float DialogueVolumeIn = SettingsSaveGame->DialogueVolume;

		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MasterSoundClass, MasterVolumeIn, 1,0,true);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MusicSoundClass,MusicVolumeIn, 1,0,true);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,SFXSoundClass,SFXVolumeIn, 1,0,true);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,DialogueSoundClass,DialogueVolumeIn, 1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),MasterSoundMix);
		
	}
}

void UELSGameInstance::SaveOtherSettings(bool bUseLeftHanded)
{
	if (SettingsSaveGame)
	{
		SettingsSaveGame->bUseLeftHandedControls = bUseLeftHanded;
		
		UGameplayStatics::SaveGameToSlot(SettingsSaveGame,FString(TEXT("settings")), 0);
	}
}

USettingsSaveGame* UELSGameInstance::LoadOtherSettings()
{
	LoadSettings();
	return SettingsSaveGame;
}

void UELSGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	UE_LOG(LogTemp, Warning, TEXT("OnMapChangeFinished"));
	if (!NewWorld) return;
	for (TObjectIterator<APuzzle> It; It; ++It)
	{
		if (It->GetWorld() != NewWorld)
			continue;

		if (It)
		{
			It->OwningManager = UPuzzleRiverManager::StaticClass();
			
		}
	}
	
	

	LoadDone();
}


void UELSGameInstance::OnMapChangeFinished(const UWorld* World)
{
	
}

void UELSGameInstance::LoadSettings()
{
	
	if (UGameplayStatics::DoesSaveGameExist(FString(TEXT("settings")), 0))
	{
		SettingsSaveGame = Cast<USettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("settings")), 0));
		
	}else
	{
		SettingsSaveGame = Cast<USettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(USettingsSaveGame::StaticClass()));
		
		if (SettingsSaveGame)
		{
			
			bool Success = UGameplayStatics::SaveGameToSlot(SettingsSaveGame,FString(TEXT("settings")), 0);
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
	
}

void UELSGameInstance::PauseMusic()
{
	if (ActiveMusicPlayer)
	{
		ActiveMusicPlayer->SetPaused(true);
	}
}

void UELSGameInstance::ResumeMusic()
{
	if (ActiveMusicPlayer)
	{
		ActiveMusicPlayer->SetPaused(false);
	}
}


void UELSGameInstance::Init()
{
	Super::Init();
	LoadSettings();
	UGameUserSettings::GetGameUserSettings()->LoadSettings();
	
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("LoadAudioSettings"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, .1f, false);
	
	if (GEngine)
	{
		// Example delegate for when a travel is requested (before the actual map load starts)
		
        
		// Example delegate for when a map has finished loading
		FWorldDelegates::OnPostWorldCreation.AddUFunction(this, "OnMapChangeFinished");
	}
	
	UDialogueSubsystem* DialogueSubsystem = GetSubsystem<UDialogueSubsystem>();
	FOnCameraChange& OnCameraChange = DialogueSubsystem->GetOnCameraChange();
	OnCameraChange.AddUObject(this,&UELSGameInstance::OnCameraChanged);
	

	
}
