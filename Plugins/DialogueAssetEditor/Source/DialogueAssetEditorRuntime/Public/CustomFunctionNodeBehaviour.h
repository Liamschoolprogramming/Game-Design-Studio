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
		
		//we get all objects of the given class type
		TArray<UObject*> Objects;
		GetObjectsOfClass(EndNodeInfo->TargetClass, Objects);
		//then iterate over each of them
		for (UObject* Object : Objects)
		{
			if (!Object)
			{
				UE_LOG(LogTemp, Warning, TEXT("Object is null"));
				continue;
			}
			//we then try to find a UFUNCTION() defined function in that class, with the given FunctionName
			UFunction* Function = Object->FindFunction(FName(EndNodeInfo->FunctionName));
			if (!Function)
			{
				UE_LOG(LogTemp, Warning, TEXT("Function name is null"));
				continue;
			}
			UE_LOG(LogTemp, Warning, TEXT("Function name: %s"), *Function->GetName());
			UE_LOG(LogTemp, Warning, TEXT("About to iterate param"))
			//we create a buffer that is the size of the functions param buffer
			uint8* Buffer = static_cast<uint8*>(FMemory_Alloca(Function->ParmsSize));
			FMemory::Memzero(Buffer, Function->ParmsSize);
			
			//we iterate over each property in the buffer
			for (TFieldIterator<FProperty> It(Function); It; ++It)
			{
				FProperty* Prop = *It;
				//we make sure its only a property that we care about
				//a regular parm, not an output and not a return
				if (!Prop->HasAnyPropertyFlags(CPF_Parm)|| Prop->HasAnyPropertyFlags(CPF_OutParm)) continue;
				if (Prop->HasAnyPropertyFlags(CPF_ReturnParm))continue;
				
				//we try to get the parameter from the given map that matches this property
				FString* Value = EndNodeInfo->Parameters.Find(Prop->GetFName());

				
				if (!Value) continue;
				UE_LOG(LogTemp, Warning, TEXT("Param found "));
				//we need to check if its a soft object reference
				// we have a different setup for TSoftObjectPtr
				if (const FSoftObjectProperty* SoftProp = CastField<FSoftObjectProperty>(Prop))
				{
					void* ParamPtr = SoftProp->ContainerPtrToValuePtr<void>(Buffer);

					// Construct FSoftObjectPath from the string (essentially copy the path)
					const TPropertyTypeFundamentals<FSoftObjectPtr>::TCppType Path(*Value);

					// Assign it directly to the property's memory
					SoftProp->SetPropertyValue(ParamPtr, Path);
					continue;
				}
				
				// in the other case for simple object types we just use a simple from string value
				Prop->ImportText_Direct(**Value,Prop->ContainerPtrToValuePtr<void>(Buffer), Object, PPF_None);
				
				
			}
			//now we call the function
			UE_LOG(LogTemp, Warning, TEXT("Calling Function"));
			Object->ProcessEvent(Function, Buffer);
		}
		//choose next option to continue dialogue
		Handler->ChooseOption(0);
	}
};
