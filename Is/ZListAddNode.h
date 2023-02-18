#pragma once
#include "ZScriptNode.h"
#include <string>

class ZExpressionNode;

class ZListAddNode : public ZScriptNode
{
public:
	ZContextVar* Exec(const std::vector<ZContextVar*>& params);
	void SetExpr(ZExpressionNode* expr);
	void SetName(std::string);
private:

	ZExpressionNode* mValueExpr;
	std::string listName;
	size_t mNameHash;

};

