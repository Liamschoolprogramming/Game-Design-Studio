#pragma once

#include "CoreMinimal.h"
#include "Core/Managers/GameManagerBase.h"
#include "Managers/InventoryManager.h"
#include "TutorialManager.generated.h"

UENUM(Blueprintable)
enum class ETutorialStage : uint8
{
	NotStarted UMETA(DisplayName = "NotStarted"),
	InProgress UMETA(DisplayName = "InProgress"),
	Completed UMETA(DisplayName = "Completed"),
};

UCLASS()
class GAMEDESIGNSTUDIO_API UTutorialManager : public UGameManagerBase
{
	GENERATED_BODY()
	
	virtual void Initialize(UGameManagerSubsystem* InstanceOwner) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, ETutorialStage> TutorialProgress;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETutorialStage GetCurrentStage(FName Tutorial);
	
	UFUNCTION(BlueprintCallable)
	void SetTutorialStage(FName Tutorial, ETutorialStage Stage);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsComplete(FName Tutorial);
	
};