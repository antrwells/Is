#pragma once
#include "ZParseNode.h"
class ZParseTransient :
    public ZParseNode
{
public:

    ZParseTransient(ZTokenStream* stream);
	ZScriptNode* Parse();
    

};

