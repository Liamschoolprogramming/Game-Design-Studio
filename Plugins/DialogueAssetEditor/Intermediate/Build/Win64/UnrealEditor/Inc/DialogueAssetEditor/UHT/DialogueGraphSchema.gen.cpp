// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DialogueGraphSchema.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueGraphSchema() {}

// ********** Begin Cross Module References ********************************************************
DIALOGUEASSETEDITOR_API UClass* Z_Construct_UClass_UDialogueGraphSchema();
DIALOGUEASSETEDITOR_API UClass* Z_Construct_UClass_UDialogueGraphSchema_NoRegister();
DIALOGUEASSETEDITOR_API UScriptStruct* Z_Construct_UScriptStruct_FNewNodeAction();
ENGINE_API UClass* Z_Construct_UClass_UEdGraphSchema();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FEdGraphSchemaAction();
UPackage* Z_Construct_UPackage__Script_DialogueAssetEditor();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDialogueGraphSchema *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueGraphSchema;
UClass* UDialogueGraphSchema::GetPrivateStaticClass()
{
	using TClass = UDialogueGraphSchema;
	if (!Z_Registration_Info_UClass_UDialogueGraphSchema.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueGraphSchema"),
			Z_Registration_Info_UClass_UDialogueGraphSchema.InnerSingleton,
			StaticRegisterNativesUDialogueGraphSchema,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UDialogueGraphSchema.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueGraphSchema_NoRegister()
{
	return UDialogueGraphSchema::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueGraphSchema_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DialogueGraphSchema.h" },
		{ "ModuleRelativePath", "Public/DialogueGraphSchema.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueGraphSchema constinit property declarations ***********************
// ********** End Class UDialogueGraphSchema constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueGraphSchema>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueGraphSchema_Statics
UObject* (*const Z_Construct_UClass_UDialogueGraphSchema_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEdGraphSchema,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueGraphSchema_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueGraphSchema_Statics::ClassParams = {
	&UDialogueGraphSchema::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueGraphSchema_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueGraphSchema_Statics::Class_MetaDataParams)
};
void UDialogueGraphSchema::StaticRegisterNativesUDialogueGraphSchema()
{
}
UClass* Z_Construct_UClass_UDialogueGraphSchema()
{
	if (!Z_Registration_Info_UClass_UDialogueGraphSchema.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueGraphSchema.OuterSingleton, Z_Construct_UClass_UDialogueGraphSchema_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueGraphSchema.OuterSingleton;
}
UDialogueGraphSchema::UDialogueGraphSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueGraphSchema);
UDialogueGraphSchema::~UDialogueGraphSchema() {}
// ********** End Class UDialogueGraphSchema *********************************************************

// ********** Begin ScriptStruct FNewNodeAction ****************************************************
struct Z_Construct_UScriptStruct_FNewNodeAction_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FNewNodeAction); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNewNodeAction); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/DialogueGraphSchema.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNewNodeAction constinit property declarations ********************
// ********** End ScriptStruct FNewNodeAction constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNewNodeAction>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FNewNodeAction_Statics
static_assert(std::is_polymorphic<FNewNodeAction>() == std::is_polymorphic<FEdGraphSchemaAction>(), "USTRUCT FNewNodeAction cannot be polymorphic unless super FEdGraphSchemaAction is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNewNodeAction;
class UScriptStruct* FNewNodeAction::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FNewNodeAction.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FNewNodeAction.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNewNodeAction, (UObject*)Z_Construct_UPackage__Script_DialogueAssetEditor(), TEXT("NewNodeAction"));
	}
	return Z_Registration_Info_UScriptStruct_FNewNodeAction.OuterSingleton;
	}
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNewNodeAction_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditor,
	Z_Construct_UScriptStruct_FEdGraphSchemaAction,
	&NewStructOps,
	"NewNodeAction",
	nullptr,
	0,
	sizeof(FNewNodeAction),
	alignof(FNewNodeAction),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNewNodeAction_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNewNodeAction_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNewNodeAction()
{
	if (!Z_Registration_Info_UScriptStruct_FNewNodeAction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNewNodeAction.InnerSingleton, Z_Construct_UScriptStruct_FNewNodeAction_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNewNodeAction.InnerSingleton);
}
// ********** End ScriptStruct FNewNodeAction ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FNewNodeAction::StaticStruct, Z_Construct_UScriptStruct_FNewNodeAction_Statics::NewStructOps, TEXT("NewNodeAction"),&Z_Registration_Info_UScriptStruct_FNewNodeAction, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNewNodeAction), 4090515245U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueGraphSchema, UDialogueGraphSchema::StaticClass, TEXT("UDialogueGraphSchema"), &Z_Registration_Info_UClass_UDialogueGraphSchema, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueGraphSchema), 3514377015U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_1571455079{
	TEXT("/Script/DialogueAssetEditor"),
	Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueGraphSchema_h__Script_DialogueAssetEditor_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
