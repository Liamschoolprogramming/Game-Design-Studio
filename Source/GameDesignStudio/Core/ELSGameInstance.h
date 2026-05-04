// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsSaveGame.h"
#include "Engine/GameInstance.h"
#include "Puzzles/Puzzle.h"
#include "ELSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDESIGNSTUDIO_API UELSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PlayMusic(USoundBase* Music, float InFadeOutTimeOld, float InFadeInTimeNew);

	UFUNCTION(BlueprintCallable, Category = "Music")
	void StopMusic(float FadeOutTime);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveAudioSettings(float MusicVolumeIn, float SFXVolumeIn, float MasterVolumeIn, float DialogueVolumeIn);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadAudioSettings();
	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveOtherSettings(bool bUseLeftHanded);

	UFUNCTION(BlueprintCallable, Category = "Save")
	USettingsSaveGame* LoadOtherSettings();
	
	
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
    
	UFUNCTION()
	void OnMapChangeFinished(const UWorld* World);

	
	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadSettings();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save", SaveGame)
	USettingsSaveGame* SettingsSaveGame;
	
	UFUNCTION(BlueprintCallable, Category = "Music")
	void PauseMusic();
	UFUNCTION(BlueprintCallable, Category = "Music")
	void ResumeMusic();

	

	UFUNCTION(BlueprintImplementableEvent)
	void LoadDone();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundBase* CurrentMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundMix* MasterSoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundClass* MasterSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundClass* DialogueSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundClass* MusicSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	USoundClass* SFXSoundClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	float FadeOutTimeOld;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	float FadeInTimeNew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	UAudioComponent* ActiveMusicPlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	UAudioComponent* FadeOutMusicPlayer;
	
	
	
protected:
	virtual void Init() override;
	
};
