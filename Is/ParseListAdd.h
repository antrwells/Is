#pragma once
#include "ZParseNode.h"
class ZListAddNode;

//Dynamic expression storage.


class ZParseListAdd : public ZParseNode
{
public:

	ZParseListAdd(ZTokenStream* stream);
	ZScriptNode* Parse();


private:

	

};

