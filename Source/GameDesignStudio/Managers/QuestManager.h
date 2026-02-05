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
	
	UFUNCTION(BlueprintCallable)
	void ActivateQuest(FName QuestName)
	{
		FQuest* FoundQuest = Quests.Find(QuestName);
		if (FoundQuest != nullptr)
		{
			FoundQuest->Active = true;
		}
	}
};
