// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DialogueAssetFactory.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueAssetFactory() {}

// ********** Begin Cross Module References ********************************************************
DIALOGUEASSETEDITOR_API UClass* Z_Construct_UClass_UDialogueAssetFactory();
DIALOGUEASSETEDITOR_API UClass* Z_Construct_UClass_UDialogueAssetFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UFactory();
UPackage* Z_Construct_UPackage__Script_DialogueAssetEditor();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDialogueAssetFactory ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueAssetFactory;
UClass* UDialogueAssetFactory::GetPrivateStaticClass()
{
	using TClass = UDialogueAssetFactory;
	if (!Z_Registration_Info_UClass_UDialogueAssetFactory.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueAssetFactory"),
			Z_Registration_Info_UClass_UDialogueAssetFactory.InnerSingleton,
			StaticRegisterNativesUDialogueAssetFactory,
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
	return Z_Registration_Info_UClass_UDialogueAssetFactory.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueAssetFactory_NoRegister()
{
	return UDialogueAssetFactory::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueAssetFactory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DialogueAssetFactory.h" },
		{ "ModuleRelativePath", "Public/DialogueAssetFactory.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueAssetFactory constinit property declarations **********************
// ********** End Class UDialogueAssetFactory constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueAssetFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueAssetFactory_Statics
UObject* (*const Z_Construct_UClass_UDialogueAssetFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAssetFactory_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueAssetFactory_Statics::ClassParams = {
	&UDialogueAssetFactory::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueAssetFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueAssetFactory_Statics::Class_MetaDataParams)
};
void UDialogueAssetFactory::StaticRegisterNativesUDialogueAssetFactory()
{
}
UClass* Z_Construct_UClass_UDialogueAssetFactory()
{
	if (!Z_Registration_Info_UClass_UDialogueAssetFactory.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueAssetFactory.OuterSingleton, Z_Construct_UClass_UDialogueAssetFactory_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueAssetFactory.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueAssetFactory);
UDialogueAssetFactory::~UDialogueAssetFactory() {}
// ********** End Class UDialogueAssetFactory ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueAssetFactory_h__Script_DialogueAssetEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueAssetFactory, UDialogueAssetFactory::StaticClass, TEXT("UDialogueAssetFactory"), &Z_Registration_Info_UClass_UDialogueAssetFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueAssetFactory), 3815713455U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueAssetFactory_h__Script_DialogueAssetEditor_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueAssetFactory_h__Script_DialogueAssetEditor_3621639364{
	TEXT("/Script/DialogueAssetEditor"),
	Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueAssetFactory_h__Script_DialogueAssetEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditor_Public_DialogueAssetFactory_h__Script_DialogueAssetEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
