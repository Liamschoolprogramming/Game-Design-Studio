// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DialogueAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueAsset() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueAsset();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueAsset_NoRegister();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueRuntimeGraph_NoRegister();
UPackage* Z_Construct_UPackage__Script_DialogueAssetEditorRuntime();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDialogueAsset *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueAsset;
UClass* UDialogueAsset::GetPrivateStaticClass()
{
	using TClass = UDialogueAsset;
	if (!Z_Registration_Info_UClass_UDialogueAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueAsset"),
			Z_Registration_Info_UClass_UDialogueAsset.InnerSingleton,
			StaticRegisterNativesUDialogueAsset,
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
	return Z_Registration_Info_UClass_UDialogueAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueAsset_NoRegister()
{
	return UDialogueAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "DialogueAsset.h" },
		{ "ModuleRelativePath", "Public/DialogueAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SomeData_MetaData[] = {
		{ "Category", "DialogueAsset" },
		{ "ModuleRelativePath", "Public/DialogueAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SomeNumber_MetaData[] = {
		{ "Category", "DialogueAsset" },
		{ "ModuleRelativePath", "Public/DialogueAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SomeBool_MetaData[] = {
		{ "Category", "DialogueAsset" },
		{ "ModuleRelativePath", "Public/DialogueAsset.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Graph_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueAsset.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueAsset constinit property declarations *****************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SomeData;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SomeNumber;
	static void NewProp_SomeBool_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_SomeBool;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Graph;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueAsset constinit property declarations *******************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueAsset_Statics

// ********** Begin Class UDialogueAsset Property Definitions ****************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeData = { "SomeData", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueAsset, SomeData), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SomeData_MetaData), NewProp_SomeData_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeNumber = { "SomeNumber", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueAsset, SomeNumber), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SomeNumber_MetaData), NewProp_SomeNumber_MetaData) };
void Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeBool_SetBit(void* Obj)
{
	((UDialogueAsset*)Obj)->SomeBool = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeBool = { "SomeBool", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UDialogueAsset), &Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeBool_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SomeBool_MetaData), NewProp_SomeBool_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueAsset_Statics::NewProp_Graph = { "Graph", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueAsset, Graph), Z_Construct_UClass_UDialogueRuntimeGraph_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Graph_MetaData), NewProp_Graph_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueAsset_Statics::NewProp_SomeBool,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueAsset_Statics::NewProp_Graph,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAsset_Statics::PropPointers) < 2048);
// ********** End Class UDialogueAsset Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_UDialogueAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditorRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueAsset_Statics::ClassParams = {
	&UDialogueAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UDialogueAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueAsset_Statics::Class_MetaDataParams)
};
void UDialogueAsset::StaticRegisterNativesUDialogueAsset()
{
}
UClass* Z_Construct_UClass_UDialogueAsset()
{
	if (!Z_Registration_Info_UClass_UDialogueAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueAsset.OuterSingleton, Z_Construct_UClass_UDialogueAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueAsset.OuterSingleton;
}
UDialogueAsset::UDialogueAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueAsset);
UDialogueAsset::~UDialogueAsset() {}
// ********** End Class UDialogueAsset ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueAsset_h__Script_DialogueAssetEditorRuntime_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueAsset, UDialogueAsset::StaticClass, TEXT("UDialogueAsset"), &Z_Registration_Info_UClass_UDialogueAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueAsset), 1920470328U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueAsset_h__Script_DialogueAssetEditorRuntime_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueAsset_h__Script_DialogueAssetEditorRuntime_2943138017{
	TEXT("/Script/DialogueAssetEditorRuntime"),
	Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueAsset_h__Script_DialogueAssetEditorRuntime_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueAsset_h__Script_DialogueAssetEditorRuntime_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
