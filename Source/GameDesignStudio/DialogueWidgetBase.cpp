// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidgetBase.h"

void UDialogueWidgetBase::SetNPCName(FText NameIn)
{
	NPCName = NameIn;
}

void UDialogueWidgetBase::SetDialogueText(FText NewDialogueText)
{
	DialogueText = NewDialogueText;
}
