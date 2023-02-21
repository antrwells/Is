#include "ZProgramNode.h"
#include "ZClassNode.h"
#include "ZEnumNode.h"

void ZMainNode::AddClass(ZClassNode* node) {

	mClasses.push_back(node);

}

void ZMainNode::AddStaticClass(ZClassNode* node)
{

	mStaticClasses.push_back(node);

}

std::vector<ZClassNode*> ZMainNode::GetClasses() {

	return mClasses;

}

std::vector<ZClassNode*> ZMainNode::GetStaticClasses() {

	return mStaticClasses;

}

ZClassNode* ZMainNode::GetClass(std::string name) {

	for (int i = 0; i < mClasses.size(); i++)
	{

		auto c = mClasses[i];

		if (c->GetName() == name) {

			return c;

		}

	}

	return nullptr;

}

void ZMainNode::AddEnum(ZEnumNode* node) {

	mEnums.push_back(node);

}

void ZMainNode::AddTransient(ZTransientNode* node) {

	mTransients.push_back(node);

}