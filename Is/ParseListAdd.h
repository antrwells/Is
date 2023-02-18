#pragma once
#include "ZParseNode.h"
class ZListAddNode;

class ZParseListAdd : public ZParseNode
{
public:

	ZParseListAdd(ZTokenStream* stream);
	ZScriptNode* Parse();


private:

	

};

