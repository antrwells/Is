#include "ZListAddNode.h"
#include "ZExpressionNode.h"
#include "ZScriptContext.h"
#include "ZContextScope.h"

void ZListAddNode::SetExpr(ZExpressionNode* node)
{

	mValueExpr = node;

}

void ZListAddNode::SetName(std::string name) {

	listName = name;
	std::hash<std::string> hasher;
	mNameHash = hasher(name);
}

ZContextVar* ZListAddNode::Exec(const std::vector<ZContextVar*>& params)
{
	auto evar = ZScriptContext::CurrentContext->GetScope()->FindVar(mNameHash);

	auto val = mValueExpr->Exec(params);

	evar->ListAdd(val);

	int a = 5;

	return nullptr;
}