#pragma once
#include "ZScriptNode.h"
#include <string>


class ZClassNode;
class ZEnumNode;
class ZTransientNode;

class ZMainNode : ZScriptNode
{
public:


	void AddClass(ZClassNode* node);
	void AddStaticClass(ZClassNode* node);
	std::vector<ZClassNode*> GetClasses();
	std::vector<ZClassNode*> GetStaticClasses();
	ZClassNode* GetClass(std::string name);
	void AddEnum(ZEnumNode* node);
	//
	std::vector<ZEnumNode*> GetEnums() {
		return mEnums;
	}
	void AddTransient(ZTransientNode* node);
	std::vector<ZTransientNode*> GetTransients() {
		return mTransients;
	}

private:

	std::vector<ZClassNode*> mClasses;
	std::vector<ZClassNode*> mStaticClasses;
	std::vector<ZTransientNode*> mTransients;
	std::vector<ZEnumNode*> mEnums;

};

