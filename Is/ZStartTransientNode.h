#pragma once
#include "ZScriptNode.h"
#include <string>

class ZStartTransientNode :
    public ZScriptNode
{
public:

    void SetTransientName(std::string name);
    ZContextVar* Exec(const std::vector<ZContextVar*>& params);


private:

    std::string mStartName = "";

};

