#pragma once
#include "ZScriptNode.h"
#include <vector>
#include <string>

class ZEnumNode :
    public ZScriptNode
{
public:

    ZEnumNode();
    void AddOption(std::string name);
    int GetOptionIndex(std::string name);
    std::string GetName()
    {
        return name;
    }
    void SetName(std::string ename) {

        name = ename;
        hashName = hasher(name);

    }
    size_t GetHashName() {
        return hashName;
    }

    int GetHashOptionIndex(size_t name) {
        
        for (int i = 0; i < hashList.size(); i++) {
            if (hashList[i] == name) {
                return i;
            }
        }

        return -1;

    }

private:

    std::string name;
    std::vector<std::string> list;
    std::vector<size_t> hashList;
    std::hash<std::string> hasher;
    size_t hashName;


};

