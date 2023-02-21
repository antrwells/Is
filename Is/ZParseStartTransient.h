#pragma once
#include "ZParseNode.h"
class ZParseStartTransient :
    public ZParseNode
{
public:

    ZParseStartTransient(ZTokenStream* stream);
	ZScriptNode* Parse();

};

