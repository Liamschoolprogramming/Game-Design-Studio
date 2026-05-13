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
