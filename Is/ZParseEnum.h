#pragma once
#include "ZParseNode.h"
#include "ZScriptNode.h"
class ZParseEnum :
    public ZParseNode
{
public:

    ZParseEnum(ZTokenStream* stream);
    ZScriptNode* Parse();

};

