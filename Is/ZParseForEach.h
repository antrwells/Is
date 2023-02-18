#pragma once
#include "ZParseNode.h"

class ZParseForEach :  public ZParseNode
{
public:

	ZParseForEach(ZTokenStream* stream);
	ZScriptNode* Parse();


};

