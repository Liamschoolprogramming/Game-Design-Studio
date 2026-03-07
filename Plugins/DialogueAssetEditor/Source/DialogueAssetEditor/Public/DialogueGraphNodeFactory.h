#pragma once
#include "DialogueGraphNodeBase.h"

#define REGISTER_DIALOGUE_NODE(NodeTypeName, NodeClass, Category, MenuName, Tooltip, Priority, bShow) \
namespace { \
struct FAutoRegister_##NodeClass \
{ \
FAutoRegister_##NodeClass() \
{ \
FDialogueGraphNodeFactory::RegisterNode( \
{ \
NodeTypeName, \
NodeClass::StaticClass(), \
FText::FromString(Category), \
FText::FromString(MenuName), \
FText::FromString(Tooltip), \
Priority, \
bShow \
}); \
} \
}; \
static FAutoRegister_##NodeClass AutoRegister_##NodeClass; \
}

#define CREATE_GRAPH_NODE(Color, NodeTypeName, NodeInfoClass, NodeBehaviourClass, bMultipleOutputs) \
	public: \
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override; \
virtual FLinearColor GetNodeTitleColor() const override \
	{ \
		return FLinearColor(Color); \
	} \
virtual bool CanUserDeleteNode() const override { return true; }\
virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;\
virtual UEdGraphPin* CreateDefaultInputPin() override;\
	virtual void CreateDefaultOutputPins() override;\
virtual FName GetDialogueNodeType() const override\
	{\
		return NodeTypeName;\
	}\
virtual void OnPropertiesChanged() override\
	{\
	if(bMultipleOutputs)\
	{\
		SyncPinsWithResponses();\
		}\
	}\
virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;\
void SyncPinsWithResponses();\
virtual void InitNodeInfo(UObject* Owner) override\
	{\
		NodeInfo = NewObject<NodeInfoClass>(Owner);\
	}\
virtual void SetNodeInfo(class UDialogueNodeInfoBase* InNodeInfo) override\
	{\
		NodeInfo = Cast<NodeInfoClass>(InNodeInfo);\
	}\
virtual UDialogueNodeInfoBase* GetNodeInfo() const override\
	{\
		return NodeInfo;\
	}\
virtual NodeInfoClass* GetDialogueNodeInfo()\
	{\
		return NodeInfo;\
	}\
virtual void InitNodeBehaviour(UObject* Owner) override\
	{\
		NodeBehaviour = NewObject<NodeBehaviourClass>(Owner);\
	}\
virtual void SetNodeBehaviour(class UDialogueNodeBehaviour* InNodeInfo) override\
	{\
		NodeBehaviour = Cast<NodeBehaviourClass>(InNodeInfo);\
	}\
virtual UDialogueNodeBehaviour* GetNodeBehaviour() const override\
	{\
		return NodeBehaviour;\
	}\
protected:\
UPROPERTY()\
	class NodeBehaviourClass* NodeBehaviour = nullptr;\
protected:\
UPROPERTY()\
class NodeInfoClass* NodeInfo = nullptr;\
private:\
	void HandleDeleteNode();\
	void HandleDeletePin();\
	void HandleAddPin();\


FORCEINLINE FString ToFString(const FText& Val) { return Val.ToString(); }
FORCEINLINE FString ToFString(const FString& Val) { return Val; }
FORCEINLINE FString ToFString(const FName& Val) { return Val.ToString(); }
FORCEINLINE FString ToFString(const int& Val) { return LexToString(Val); }


#define NODE_TITLE(NodeClass, TitleName, TitleVariable)\
FText NodeClass::GetNodeTitle(ENodeTitleType::Type TitleType) const\
{\
	if (NodeInfo != nullptr)\
	{\
		FString OutputString = TitleName;\
		if (!ToFString(NodeInfo->TitleVariable).IsEmpty())\
		{\
			FString ActionData = ToFString(NodeInfo->TitleVariable);\
			if (ActionData.Len() > 15)\
			{\
				ActionData = ActionData.Left(15) + TEXT("...");\
			}\
			OutputString += TEXT(" - ") + ActionData;\
		}\
		return FText::FromString(OutputString);\
	}\
	return FText::FromString(TitleName);\
}\

#define GET_CONTEXT_ACTION(NodeClass)\
void NodeClass::GetNodeContextMenuActions(class UToolMenu* Menu,\
	class UGraphNodeContextMenuContext* Context) const\
{\
	FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));\
	section.AddMenuEntry(\
		TEXT("DeleteEntry"),\
		FText::FromString(TEXT("Delete Node")),\
		FText::FromString(TEXT("Deletes the node")),\
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),\
		FUIAction(FExecuteAction::CreateUObject(\
			const_cast<NodeClass*>(this),\
			&NodeClass::HandleDeleteNode\
			)\
		)\
	);\
}\
void NodeClass::HandleDeleteNode()\
{\
GetGraph()->RemoveNode(this);\
}\

#define GET_CONTEXT_ACTION_MULTI(NodeClass,NodeInfoClass, ResponseVariable)\
void NodeClass::GetNodeContextMenuActions(class UToolMenu* Menu,\
class UGraphNodeContextMenuContext* Context) const\
{\
FToolMenuSection& section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));\
section.AddMenuEntry(\
TEXT("DeleteEntry"),\
FText::FromString(TEXT("Delete Node")),\
FText::FromString(TEXT("Deletes the node")),\
FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),\
FUIAction(FExecuteAction::CreateUObject(\
const_cast<NodeClass*>(this),\
&NodeClass::HandleDeleteNode\
)\
)\
);\
section.AddMenuEntry(\
		TEXT("AddPinEntry"),\
		FText::FromString(TEXT("Add Response")),\
		FText::FromString(TEXT("Creates a new response")),\
		FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeAddPinIcon")),\
		FUIAction(FExecuteAction::CreateUObject(\
			const_cast<NodeClass*>(this),\
			&NodeClass::HandleAddPin\
			)\
		)\
	);\
section.AddMenuEntry(\
	TEXT("DeletePinEntry"),\
	FText::FromString(TEXT("Delete Response")),\
	FText::FromString(TEXT("Deletes the last response")),\
	FSlateIcon(TEXT("DialogueAssetEditorStyle"),TEXT("DialogueAssetEditor.NodeDeletePinIcon")),\
	FUIAction(FExecuteAction::CreateUObject(\
		const_cast<NodeClass*>(this),\
		&NodeClass::HandleDeletePin\
		)\
	)\
);\
}\
void NodeClass::HandleDeleteNode()\
{\
GetGraph()->RemoveNode(this);\
}\
void NodeClass::HandleAddPin()\
{\
	NodeInfoClass* DialogueNodeInfo = Cast<NodeInfoClass>(GetNodeInfo());\
	DialogueNodeInfo->ResponseVariable.Add(FText::FromString(TEXT("Response")));\
	SyncPinsWithResponses();\
	GetGraph()->NotifyGraphChanged();\
	GetGraph()->Modify();\
}\
void NodeClass::HandleDeletePin()\
{\
	UEdGraphPin* Pin = GetPinAt(Pins.Num() - 1);\
	if (Pin->Direction != EGPD_Input)\
	{\
		NodeInfoClass* DialogueNodeInfo = Cast<NodeInfoClass>(GetNodeInfo());\
		DialogueNodeInfo->ResponseVariable.RemoveAt(DialogueNodeInfo->ResponseVariable.Num() - 1);\
		SyncPinsWithResponses();\
		GetGraph()->NotifyGraphChanged();\
		GetGraph()->Modify();\
	}\
}\


#define CREATE_PINS(NodeClass, PinCategory, ...)\
UEdGraphPin* NodeClass::CreateDefaultInputPin()\
{\
return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));\
}\
void NodeClass::CreateDefaultOutputPins()\
{\
FString GenPins[] = { __VA_ARGS__ };\
for (FString PinName : GenPins)\
{\
CreateDialoguePin(EGPD_Output, FName(PinName));\
}\
}\
UEdGraphPin* NodeClass::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)\
{\
FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");\
FName SubCategory = PinCategory;\
UEdGraphPin* Pin = CreatePin(\
Direction,\
Category,\
Name);\
Pin->PinType.PinSubCategory = SubCategory;\
return Pin;\
}\


#define CREATE_PINS_RESPONSES(NodeClass, PinCategory, ResponseVariable, ...)\
UEdGraphPin* NodeClass::CreateDefaultInputPin()\
{\
return CreateDialoguePin(EGPD_Input, TEXT("FlowInput"));\
}\
void NodeClass::CreateDefaultOutputPins()\
{\
FString GenPins[] = { __VA_ARGS__ };\
for (FString PinName : GenPins)\
{\
CreateDialoguePin(EGPD_Output, FName(PinName));\
}\
for (auto PinName : NodeInfo->ResponseVariable)\
{\
CreateDialoguePin(EGPD_Output, FName( ToFString(PinName)));\
}\
}\
UEdGraphPin* NodeClass::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)\
{\
FName Category = (Direction == EGPD_Input) ? TEXT("Input") : TEXT("Output");\
FName SubCategory = PinCategory;\
UEdGraphPin* Pin = CreatePin(\
Direction,\
Category,\
Name);\
Pin->PinType.PinSubCategory = SubCategory;\
return Pin;\
}\

struct FDialogueNodeRegistration
{
	FName NodeType;
	TSubclassOf<UDialogueGraphNodeBase> GraphNodeClass;

	FText Category;
	FText MenuName;
	FText Tooltip;
	int32 Priority;
	bool bShowInContextMenu = true;
};

using FNodeFactoryFunc = TFunction<UDialogueGraphNodeBase*(UObject* Outer)>;



class FDialogueGraphNodeFactory
{
public:
	static void RegisterNode(const FDialogueNodeRegistration& Registration)
	{
		GetRegistry().Add(Registration);
	}

	static UDialogueGraphNodeBase* CreateNode(
	FName NodeType,
	UObject* Outer)
	{
		for (const FDialogueNodeRegistration& Node : GetAllNodes())
		{
			if (Node.NodeType.IsEqual( NodeType))
			{
				return NewObject<UDialogueGraphNodeBase>(
					Outer,
					Node.GraphNodeClass
				);
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Unknown NodeType: %s"), *NodeType.ToString());
		return nullptr;
	}
	static const TArray<FDialogueNodeRegistration>& GetAllNodes()
	{
		return GetRegistry();
	}

private:
	static TArray<FDialogueNodeRegistration>& GetRegistry()
	{
		static TArray<FDialogueNodeRegistration> Registry;
		return Registry;
	}
};