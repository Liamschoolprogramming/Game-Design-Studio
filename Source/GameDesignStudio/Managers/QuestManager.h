#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Data/QuestData.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UELSSaveGame;

UCLASS()
class GAMEDESIGNSTUDIO_API UQuestManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	// Quests are mapped by their Item Key Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FQuest> Quests;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* QuestMenu;
	
	void InitializeQuests();
	
	UFUNCTION(BlueprintCallable)
	bool IsQuestForItemActive(FName ItemName); 
	
	UFUNCTION(BlueprintCallable)
	void ActivateQuestForItem(FName ItemName);
	
	UFUNCTION(BlueprintCallable)
	void ProvideReward(FName ItemName);
	
	UFUNCTION(BlueprintCallable)
	bool CompleteQuest(FName ItemName);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanCompleteQuest(FName ItemName);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<int> GetQuestProgress(FName ItemName);
	
	UFUNCTION(BlueprintCallable)
	void UpdateQuestProgress(FName ItemName);
	
	UFUNCTION(BlueprintCallable)
	EQuestState GetQuestState(FName ItemName);
	
	
};

inline void UQuestManager::InitializeQuests()
{
	Quests = {
		//Day Quest - Sundew
		{
			"Sunstone",
			FQuest(
				"Flower Spirit Sundew",
				"A cheery sunflower spirit wants to live closer to the goddess but it's too cold. Find a Sunstone to heat up its living space.",
				"Sunstone",
				1,
				EPlayerBoostableStat::Mind,
				5,
				"None"
			)
		},
		//Night Quest - Stoneface
		{
			"Golem",
			FQuest(
				"Self-Aware Golem",
				"The Golem wants someone to talk to.",
				"Golem",
				1,
				EPlayerBoostableStat::Health,
				10,
				"None"
			)
		},
		//Lehan Quest - Whistlebranch
		{
			"Owl Child",
			FQuest(
				"Whistlebranch's Missing Children",
				"Whistlebranch can't seem to find her children. Help her find all 4 of them.",
				"Owl Child",
				4,
				EPlayerBoostableStat::Stamina,
				5,
				"None"
			)
		},
		
		//Lehan Quest - Verdan
		{
			"Berry",
			FQuest(
				"Verdan's Request",
				"Verdan wants you to collect 10 berries to help the local wildlife.",
				"Berry",
				10,
				EPlayerBoostableStat::Stamina,
				0,
				"Aegis Charm"
			)
		},
	};
}
