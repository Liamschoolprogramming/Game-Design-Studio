// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ELSGameInstance.h"

#include "Components/AudioComponent.h"
#include "Debug/DebugUtils.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

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
			ActiveMusicPlayer = UGameplayStatics::CreateSound2D(GetWorld(),CurrentMusic);
			ActiveMusicPlayer->FadeIn(FadeInTimeNew);
		}
	}
}

void UELSGameInstance::StopMusic(float FadeOutTime)
{
	FadeOutMusicPlayer = ActiveMusicPlayer;
	FadeOutMusicPlayer->FadeOut(FadeOutTime, 0.f);
}

void UELSGameInstance::SaveAudioSettings(float MusicVolumeIn, float SFXVolumeIn, float MasterVolumeIn)
{
	if (SettingsSaveGame)
	{
		SettingsSaveGame->MusicVolume = MusicVolumeIn;
		SettingsSaveGame->SFXVolume = SFXVolumeIn;
		SettingsSaveGame->MasterVolume = MasterVolumeIn;

		if (MasterSoundMix && MusicSoundClass && SFXSoundClass && MasterSoundClass)
		{
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MasterSoundClass, MasterVolumeIn, 1,0,true);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MusicSoundClass,MusicVolumeIn, 1,0,true);
			UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,SFXSoundClass,SFXVolumeIn, 1,0,true);

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

		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MasterSoundClass, MasterVolumeIn, 1,0,true);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,MusicSoundClass,MusicVolumeIn, 1,0,true);
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(),MasterSoundMix,SFXSoundClass,SFXVolumeIn, 1,0,true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(),MasterSoundMix);
		
	}
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
	
}
