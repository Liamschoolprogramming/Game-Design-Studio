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
				"Summary",
				"A cheery sunflower spirit wants to live closer to the goddess but it's too cold. Find a Sunstone to heat up its living space.",
				"Sunstone",
				1
			)
		},
		//Night Quest - Stoneface
		{
			"Golem",
			FQuest(
				"Self-Aware Golem",
				"Summary",
				"The Golem wants someone to talk to.",
				"Golem",
				1
			)
		},
		//Lehan Quest - Whistlebranch
		{
			"Owl Child",
			FQuest(
				"Whistlebranch's Missing Children",
				"Summary",
				"Whistlebranch can't seem to find her children. Help her find all 4 of them.",
				"Owl Child",
				4
			)
		},
		
		//Lehan Quest - Verdan
		{
			"Berry",
			FQuest(
				"Verdan's Request",
				"Summary",
				"Verdan wants you to collect 10 berries to help the local wildlife.",
				"Berry",
				10
			)
		},
		
		//Quest - Rootwhisper
		{
			"Woodpecker",
			FQuest(
				"Rootwhisper's Problem",
				"Find the woodpecker family.",
				"Every year a family of woodpeckers helps groom Rootwhisper, but this year they are nowhere to be seen. Rootwhisper has asked you to find them.",
				"Woodpecker",
				1
			)
		},
		
		//Quest - Moldred
		{
			"Veilspore",
			FQuest(
				"Moldred's Ascension",
				"Find the Veilspore.",
				"You angered Moldred by failing to comprehend his power. If you wish to be forgiven bring the Veilspore to him.",
				"Veilspore",
				1
			)
		},
		
		//Quest - Sporax
		{
			"Mushroom",
			FQuest(
				"Friends for Sporax",
				"Find company for Sporax.",
				"Sporax spent most of their life in solitude but now desires companionship. Sporax asked you to find 10 mushrooms to comfort them.",
				"Mushroom",
				10
			)
		},
	};
}
