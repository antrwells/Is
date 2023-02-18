#include "ZEnumNode.h"

ZEnumNode::ZEnumNode() {

}

void ZEnumNode::AddOption(std::string name) {

	list.push_back(name);
	hashList.push_back(hasher(name));

}

int ZEnumNode::GetOptionIndex(std::string name) {

	for (int i = 0; i < name.size(); i++) {
		if (list[i] == name) return i;
	}
	return -1;

}