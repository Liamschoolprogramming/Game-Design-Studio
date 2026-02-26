#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Data/QuestData.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

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
