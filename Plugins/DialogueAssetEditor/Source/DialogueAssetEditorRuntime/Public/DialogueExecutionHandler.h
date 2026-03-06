// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueEndNodeInfo.h"
#include "UObject/Interface.h"

#include "DialogueExecutionHandler.generated.h"
UENUM(BlueprintType)
enum class EDialogueParamType : uint8
{
	Int,
	Float,
	String,
	Bool
};
USTRUCT(BlueprintType)
struct FDialogueParameters
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(BlueprintReadWrite)
	EDialogueParamType Type;

	UPROPERTY(BlueprintReadWrite)
	int32 IntValue;

	UPROPERTY(BlueprintReadWrite)
	float FloatValue;

	UPROPERTY(BlueprintReadWrite)
	FString StringValue;

	UPROPERTY(BlueprintReadWrite)
	bool BoolValue;
	
};


// This class does not need to be modified.
UINTERFACE()
class UDialogueExecutionHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUEASSETEDITORRUNTIME_API IDialogueExecutionHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetDialogueText(FText InText) = 0;
	virtual void ClearResponses() = 0;
	virtual void AddResponseButton(FText InResponseText, int InOptionIndex) = 0;
	virtual void SetupCameraAndSpeaker(FName CameraName, FName InSpeakerName, UTexture2D* Portrait) = 0;
	virtual void EndDialogue(EDialogueNodeAction Action, FString ActionData) = 0;
	virtual TArray<int> GetQuestProgress(FName QuestKey) = 0;
	virtual void StartQuest(FName QuestKey) = 0;
	virtual void CompleteQuest(FName QuestKey) = 0;
	virtual void CheckQuest(FName QuestKey) = 0;
	virtual void ChangeCamera(FName CameraName, float TransitionTime, bool bReenableDialogueAfterAnimation) = 0;
	virtual UObject* GetCurrentNode() = 0;
	virtual void CallCustomFunction(FString FunctionName) = 0;
	virtual class UDialogueAsset* GetAsset() = 0;
	virtual void ChooseOption(int IndexToChoose) = 0;
	virtual UWorld* GetWorldFromPlayer() = 0;
	virtual void CheckDialogueState() = 0;
	//virtual void CallCustomFunctionWithParams(FString FunctionName, const FDialogueParameters& Parameters) = 0;
};
