// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomFunctionNodeInfo.h"
#include "DialogueNodeBehaviour.h"
#include "DialogueExecutionHandler.h"
#include "DialogueNodeInfo.h"
#include "CustomFunctionNodeBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEASSETEDITORRUNTIME_API UCustomFunctionNodeBehaviour : public UDialogueNodeBehaviour
{
	GENERATED_BODY()

	virtual void Execute(UDialogueNodeInfoBase* NodeInfoBase, IDialogueExecutionHandler* Handler) override
	{
		UCustomFunctionNodeInfo* EndNodeInfo = Cast<UCustomFunctionNodeInfo>(NodeInfoBase);
		if (EndNodeInfo == nullptr) return;
		
		UE_LOG(LogTemp, Warning, TEXT("About to iterate"));
		TArray<UObject*> Objects;
		GetObjectsOfClass(EndNodeInfo->TargetClass, Objects);
		
		for (UObject* Object : Objects)
		{
			if (!Object)
			{
				UE_LOG(LogTemp, Warning, TEXT("Object is null"));
				continue;
			}
			UFunction* Function = Object->FindFunction(FName(EndNodeInfo->FunctionName));
			if (!Function)
			{
				UE_LOG(LogTemp, Warning, TEXT("Function name is null"));
				continue;
			}
			UE_LOG(LogTemp, Warning, TEXT("Function name: %s"), *Function->GetName());
			UE_LOG(LogTemp, Warning, TEXT("About to iterate param"))
			uint8* Buffer = (uint8*)FMemory_Alloca(Function->ParmsSize);
			FMemory::Memzero(Buffer, Function->ParmsSize);
			
			
			for (TFieldIterator<FProperty> It(Function); It; ++It)
			{
				FProperty* Prop = *It;

				if (!Prop->HasAnyPropertyFlags(CPF_Parm)|| Prop->HasAnyPropertyFlags(CPF_OutParm)) continue;
				if (Prop->HasAnyPropertyFlags(CPF_ReturnParm))continue;
				
				FString* Value = EndNodeInfo->Parameters.Find(Prop->GetFName());

				if (!Value) continue;
				UE_LOG(LogTemp, Warning, TEXT("Param found "));
				
				FSoftObjectProperty* SoftProp = CastField<FSoftObjectProperty>(Prop);
				// Handle TSoftObjectPtr specially
				if (SoftProp)
				{
					void* ParamPtr = SoftProp->ContainerPtrToValuePtr<void>(Buffer);

					// Construct FSoftObjectPath from your string
					const TPropertyTypeFundamentals<FSoftObjectPtr>::TCppType Path(*Value);

					// Assign it directly to the property's memory
					SoftProp->SetPropertyValue(ParamPtr, Path);
					continue;
				}
				
				// Convert string to property value
				Prop->ImportText_Direct(**Value,Prop->ContainerPtrToValuePtr<void>(Buffer), Object, PPF_None);
				
				
			}
			UE_LOG(LogTemp, Warning, TEXT("Calling Function"));
			Object->ProcessEvent(Function, Buffer);
		}
		Handler->ChooseOption(0);
	}
};
