// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueNodeInfo.h"
#include "QuestProgressNodeInfo.h"
#include "DialogueExecutionHandler.h"
#include "QuestProgressBehaviour.generated.h"




/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UQuestProgressBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		
		UQuestProgressNodeInfo* NodeInfo = Cast<UQuestProgressNodeInfo>(NodeInfoBase);
		
		TArray<int> Progress = Handler->GetQuestProgress(NodeInfo->QuestName);
		
		FString DialogueText;
		if (NodeInfo->Dialogue != TEXT(""))
		{
			DialogueText = NodeInfo->Dialogue;
			
					
			DialogueText = DialogueText.Replace(TEXT("$total"), *NameForNumber(Progress[1]));
			DialogueText = DialogueText.Replace(TEXT("$current"), *NameForNumber(Progress[0]));
			DialogueText = DialogueText.Replace(TEXT("$remaining"), *NameForNumber(Progress[1] - Progress[0]));
					
		}
		
		Handler->SetDialogueText(FText::FromString(DialogueText));
		Handler->ClearResponses();
		Handler->AddResponseButton(FText::FromString(TEXT("Continue")),0);
				
				
			
				
	}
	
private:
	FString DigitName(int digit);
	FString TeenName(int number);
	FString TensName(int number);
	FString IntName(int number);

	TArray<FString> ones {"","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	TArray<FString> teens {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen","sixteen", "seventeen", "eighteen", "nineteen"};
	TArray<FString> tens {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

	/**
	 * 
	 * @param Number 
	 * @return the number turned into a string
	 * 
	 * this code comes from https://stackoverflow.com/questions/40252753/c-converting-number-to-words
	 * 
	 */
	FString NameForNumber (long Number) {
		if (Number == 0)
		{
			return TEXT("zero");
		}
		else if (Number < 10) {
			return ones[Number];
		} else if (Number < 20) {
			return teens [Number - 10];
		} else if (Number < 100) {
			return tens[Number / 10] + ((Number % 10 != 0) ? " " + NameForNumber(Number % 10) : "");
		} else if (Number < 1000) {
			return NameForNumber(Number / 100) + " hundred" + ((Number % 100 != 0) ? " " + NameForNumber(Number % 100) : "");
		} else if (Number < 1000000) {
			return NameForNumber(Number / 1000) + " thousand" + ((Number % 1000 != 0) ? " " + NameForNumber(Number % 1000) : "");
		} else if (Number < 1000000000) {
			return NameForNumber(Number / 1000000) + " million" + ((Number % 1000000 != 0) ? " " + NameForNumber(Number % 1000000) : "");
		} else if (Number < 1000000000000) {
			return NameForNumber(Number / 1000000000) + " billion" + ((Number % 1000000000 != 0) ? " " + NameForNumber(Number % 1000000000) : "");
		}
		return "";
	}

};
