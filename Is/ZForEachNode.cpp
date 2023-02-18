#include "ZForEachNode.h"
#include "ZContextScope.h"
#include "ZContextVar.h"
#include "ZScriptContext.h"
#include "ZCodeBodyNode.h"
#include "VarTypes.h"

void ZForEachNode::SetNames(std::string name, std::string list) {

	itemName = name;
	listName = list;

}

void ZForEachNode::SetBody(ZCodeBodyNode* node)
{

	body = node;

}

ZContextVar* ZForEachNode::Exec(const std::vector<ZContextVar*>& params)
{


	//listName = name;
	std::hash<std::string> hasher;
	size_t hash = hasher(listName);


	ZContextVar* list = ZScriptContext::CurrentContext->GetScope()->FindVar(hash);

	auto ls = list->GetList();

	if (ls.size() == 0) return nullptr;

	auto t1 = ls[0]->GetType();

	auto item_var = new ZContextVar(itemName, t1, "", false);

	ZScriptContext::CurrentContext->GetScope()->RegisterVar(item_var);

	for (int i = 0; i < ls.size(); i++)
	{

		auto val = ls[i];
		switch (t1) {
		case VarType::VarInteger:
			item_var->SetInt(val->GetIntVal());
			break;
		case VarType::VarInstance:
			item_var->SetClass(val->GetClassVal());
			break;
		case VarType::VarFloat:
			item_var->SetFloat(val->GetFloatVal());
			break;
		case VarType::VarString:
			item_var->SetString(val->GetStringVal());
			break;
		case VarType::VarList:
			item_var->SetList(val->GetList());
			break;

		}
		
		body->Exec(params);

	}

	ZScriptContext::CurrentContext->GetScope()->RemoveVar(item_var);

	return nullptr;

}