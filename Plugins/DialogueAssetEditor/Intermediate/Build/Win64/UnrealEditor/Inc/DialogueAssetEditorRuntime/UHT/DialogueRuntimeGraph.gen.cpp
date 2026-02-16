// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DialogueRuntimeGraph.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDialogueRuntimeGraph() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueeRuntimePin();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueeRuntimePin_NoRegister();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueRuntimeGraph();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueRuntimeGraph_NoRegister();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueRuntimeNode();
DIALOGUEASSETEDITORRUNTIME_API UClass* Z_Construct_UClass_UDialogueRuntimeNode_NoRegister();
UPackage* Z_Construct_UPackage__Script_DialogueAssetEditorRuntime();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDialogueeRuntimePin *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueeRuntimePin;
UClass* UDialogueeRuntimePin::GetPrivateStaticClass()
{
	using TClass = UDialogueeRuntimePin;
	if (!Z_Registration_Info_UClass_UDialogueeRuntimePin.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueeRuntimePin"),
			Z_Registration_Info_UClass_UDialogueeRuntimePin.InnerSingleton,
			StaticRegisterNativesUDialogueeRuntimePin,
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
	return Z_Registration_Info_UClass_UDialogueeRuntimePin.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueeRuntimePin_NoRegister()
{
	return UDialogueeRuntimePin::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueeRuntimePin_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DialogueRuntimeGraph.h" },
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinName_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PinId_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Connection_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueeRuntimePin constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_PinName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PinId;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Connection;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueeRuntimePin constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueeRuntimePin>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueeRuntimePin_Statics

// ********** Begin Class UDialogueeRuntimePin Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_PinName = { "PinName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueeRuntimePin, PinName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinName_MetaData), NewProp_PinName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_PinId = { "PinId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueeRuntimePin, PinId), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PinId_MetaData), NewProp_PinId_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_Connection = { "Connection", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueeRuntimePin, Connection), Z_Construct_UClass_UDialogueeRuntimePin_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Connection_MetaData), NewProp_Connection_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueeRuntimePin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_PinName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_PinId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueeRuntimePin_Statics::NewProp_Connection,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueeRuntimePin_Statics::PropPointers) < 2048);
// ********** End Class UDialogueeRuntimePin Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UDialogueeRuntimePin_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditorRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueeRuntimePin_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueeRuntimePin_Statics::ClassParams = {
	&UDialogueeRuntimePin::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UDialogueeRuntimePin_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueeRuntimePin_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueeRuntimePin_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueeRuntimePin_Statics::Class_MetaDataParams)
};
void UDialogueeRuntimePin::StaticRegisterNativesUDialogueeRuntimePin()
{
}
UClass* Z_Construct_UClass_UDialogueeRuntimePin()
{
	if (!Z_Registration_Info_UClass_UDialogueeRuntimePin.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueeRuntimePin.OuterSingleton, Z_Construct_UClass_UDialogueeRuntimePin_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueeRuntimePin.OuterSingleton;
}
UDialogueeRuntimePin::UDialogueeRuntimePin(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueeRuntimePin);
UDialogueeRuntimePin::~UDialogueeRuntimePin() {}
// ********** End Class UDialogueeRuntimePin *********************************************************

// ********** Begin Class UDialogueRuntimeNode *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueRuntimeNode;
UClass* UDialogueRuntimeNode::GetPrivateStaticClass()
{
	using TClass = UDialogueRuntimeNode;
	if (!Z_Registration_Info_UClass_UDialogueRuntimeNode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueRuntimeNode"),
			Z_Registration_Info_UClass_UDialogueRuntimeNode.InnerSingleton,
			StaticRegisterNativesUDialogueRuntimeNode,
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
	return Z_Registration_Info_UClass_UDialogueRuntimeNode.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueRuntimeNode_NoRegister()
{
	return UDialogueRuntimeNode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueRuntimeNode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DialogueRuntimeGraph.h" },
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputPin_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputPins_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueRuntimeNode constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InputPin;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OutputPins_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutputPins;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueRuntimeNode constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueRuntimeNode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueRuntimeNode_Statics

// ********** Begin Class UDialogueRuntimeNode Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_InputPin = { "InputPin", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueRuntimeNode, InputPin), Z_Construct_UClass_UDialogueeRuntimePin_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputPin_MetaData), NewProp_InputPin_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_OutputPins_Inner = { "OutputPins", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDialogueeRuntimePin_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_OutputPins = { "OutputPins", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueRuntimeNode, OutputPins), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputPins_MetaData), NewProp_OutputPins_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueRuntimeNode, Position), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueRuntimeNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_InputPin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_OutputPins_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_OutputPins,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeNode_Statics::NewProp_Position,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeNode_Statics::PropPointers) < 2048);
// ********** End Class UDialogueRuntimeNode Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UDialogueRuntimeNode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditorRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeNode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueRuntimeNode_Statics::ClassParams = {
	&UDialogueRuntimeNode::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UDialogueRuntimeNode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeNode_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeNode_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueRuntimeNode_Statics::Class_MetaDataParams)
};
void UDialogueRuntimeNode::StaticRegisterNativesUDialogueRuntimeNode()
{
}
UClass* Z_Construct_UClass_UDialogueRuntimeNode()
{
	if (!Z_Registration_Info_UClass_UDialogueRuntimeNode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueRuntimeNode.OuterSingleton, Z_Construct_UClass_UDialogueRuntimeNode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueRuntimeNode.OuterSingleton;
}
UDialogueRuntimeNode::UDialogueRuntimeNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueRuntimeNode);
UDialogueRuntimeNode::~UDialogueRuntimeNode() {}
// ********** End Class UDialogueRuntimeNode *********************************************************

// ********** Begin Class UDialogueRuntimeGraph ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDialogueRuntimeGraph;
UClass* UDialogueRuntimeGraph::GetPrivateStaticClass()
{
	using TClass = UDialogueRuntimeGraph;
	if (!Z_Registration_Info_UClass_UDialogueRuntimeGraph.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DialogueRuntimeGraph"),
			Z_Registration_Info_UClass_UDialogueRuntimeGraph.InnerSingleton,
			StaticRegisterNativesUDialogueRuntimeGraph,
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
	return Z_Registration_Info_UClass_UDialogueRuntimeGraph.InnerSingleton;
}
UClass* Z_Construct_UClass_UDialogueRuntimeGraph_NoRegister()
{
	return UDialogueRuntimeGraph::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDialogueRuntimeGraph_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "DialogueRuntimeGraph.h" },
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Nodes_MetaData[] = {
		{ "ModuleRelativePath", "Public/DialogueRuntimeGraph.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDialogueRuntimeGraph constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Nodes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Nodes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDialogueRuntimeGraph constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDialogueRuntimeGraph>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDialogueRuntimeGraph_Statics

// ********** Begin Class UDialogueRuntimeGraph Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UDialogueRuntimeGraph_Statics::NewProp_Nodes_Inner = { "Nodes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDialogueRuntimeNode_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UDialogueRuntimeGraph_Statics::NewProp_Nodes = { "Nodes", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UDialogueRuntimeGraph, Nodes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Nodes_MetaData), NewProp_Nodes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDialogueRuntimeGraph_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeGraph_Statics::NewProp_Nodes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDialogueRuntimeGraph_Statics::NewProp_Nodes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeGraph_Statics::PropPointers) < 2048);
// ********** End Class UDialogueRuntimeGraph Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UDialogueRuntimeGraph_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_DialogueAssetEditorRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeGraph_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDialogueRuntimeGraph_Statics::ClassParams = {
	&UDialogueRuntimeGraph::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UDialogueRuntimeGraph_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeGraph_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDialogueRuntimeGraph_Statics::Class_MetaDataParams), Z_Construct_UClass_UDialogueRuntimeGraph_Statics::Class_MetaDataParams)
};
void UDialogueRuntimeGraph::StaticRegisterNativesUDialogueRuntimeGraph()
{
}
UClass* Z_Construct_UClass_UDialogueRuntimeGraph()
{
	if (!Z_Registration_Info_UClass_UDialogueRuntimeGraph.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDialogueRuntimeGraph.OuterSingleton, Z_Construct_UClass_UDialogueRuntimeGraph_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDialogueRuntimeGraph.OuterSingleton;
}
UDialogueRuntimeGraph::UDialogueRuntimeGraph(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDialogueRuntimeGraph);
UDialogueRuntimeGraph::~UDialogueRuntimeGraph() {}
// ********** End Class UDialogueRuntimeGraph ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueRuntimeGraph_h__Script_DialogueAssetEditorRuntime_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDialogueeRuntimePin, UDialogueeRuntimePin::StaticClass, TEXT("UDialogueeRuntimePin"), &Z_Registration_Info_UClass_UDialogueeRuntimePin, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueeRuntimePin), 3962741043U) },
		{ Z_Construct_UClass_UDialogueRuntimeNode, UDialogueRuntimeNode::StaticClass, TEXT("UDialogueRuntimeNode"), &Z_Registration_Info_UClass_UDialogueRuntimeNode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueRuntimeNode), 3027090252U) },
		{ Z_Construct_UClass_UDialogueRuntimeGraph, UDialogueRuntimeGraph::StaticClass, TEXT("UDialogueRuntimeGraph"), &Z_Registration_Info_UClass_UDialogueRuntimeGraph, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDialogueRuntimeGraph), 3163678411U) },
	};
}; // Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueRuntimeGraph_h__Script_DialogueAssetEditorRuntime_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueRuntimeGraph_h__Script_DialogueAssetEditorRuntime_3106587311{
	TEXT("/Script/DialogueAssetEditorRuntime"),
	Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueRuntimeGraph_h__Script_DialogueAssetEditorRuntime_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_syste_Documents_Unreal_Projects_Game_Design_Studio_Plugins_DialogueAssetEditor_Source_DialogueAssetEditorRuntime_Public_DialogueRuntimeGraph_h__Script_DialogueAssetEditorRuntime_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
