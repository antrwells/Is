#pragma once
#include "ZScriptNode.h"
#include <string>

class ZExpressionNode;

class ZAssignNode :
    public ZScriptNode
{
public:

    void SetVarName(std::string name);
    void SetMemberName(std::string name);
    void SetValue(ZExpressionNode* val);
    void SetAccess(ZExpressionNode* acc)
    {
        mAccess = acc;
    }
    ZContextVar* Exec(const std::vector<ZContextVar*>& params);
    

private:

    std::string mVarName = "";
    std::string mMember ="";
    ZExpressionNode* mValue = nullptr;
    size_t mNameHash, mMemberHash;
    ZExpressionNode* mAccess = nullptr;

};

