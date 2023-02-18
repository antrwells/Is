#pragma once
#include "ZScriptNode.h"
#include <string>
class ZCodeBodyNode;

class ZForEachNode : public ZScriptNode
{
public:

	void SetNames(std::string item, std::string list);
	void SetBody(ZCodeBodyNode* body);
	ZContextVar* Exec(const std::vector<ZContextVar*>& params);

private:

	std::string itemName;
	std::string listName;
	ZCodeBodyNode* body;

};

