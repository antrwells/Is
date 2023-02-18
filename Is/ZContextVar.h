#pragma once
#include <string>
#include <vector>
//#include "DataTypes.h"
enum VarType;

class ZClassNode;

class ZContextVar
{
public:

	ZContextVar(std::string name,enum VarType type,std::string baseID,bool comparer);

	std::string GetName();
	size_t GetHashName();
	VarType GetType();
	int GetIntVal();
	float GetFloatVal();
	bool GetBoolVal();
	VarType GetCurrentType() {
		return mCurrentType;
	}
	
	std::string GetStringVal();
	ZClassNode* GetClassVal();
	void SetInt(int val);
	void SetFloat(float val);
	void SetString(std::string val);
	void SetClass(ZClassNode* cls);
	void SetCObj(void* obj);
	void SetBool(bool val);
	void* GetCObj();
	int GetTypeInt() {
		return (int)mType;
	}
	std::string GetBaseID() {
		return mBaseID;
	}
	void SetBaseID(std::string name) {
		mBaseID = name;
	}
	bool GetCompare() {
		return mComparer;
	}

	//For run/stop type scenarios.

	void Push();
	void Pop();

	void ListAdd(ZContextVar* var);
	std::vector<ZContextVar*> GetList() {
		return mList;
	}
	void SetList(std::vector<ZContextVar*> list) {
		mList = list;
	}

private:

	std::string mName;
	VarType mType;
	VarType mCurrentType;
	int mIntVal;
	float mFloatVal;
	bool mBoolVal;
	bool mPushBool;
	std::string mStringVal;
	ZClassNode* mClassVal;
	void* mCObj;
	float mPushFloat;
	int mPushInt;
	std::string mPushString;
	std::string mBaseID;
	bool mComparer = false;
	size_t mHashName;
	std::vector<ZContextVar*> mList;

};


ZContextVar* VMakeInt(int v,bool comparer = false);
ZContextVar* VMakeFloat(float v,bool cmparer = false);
ZContextVar* VMakeString(std::string v,bool comparer=false);
ZContextVar* VMakeC(void* v,bool comparer=false);
ZContextVar* VMakeClass(ZClassNode* v,bool comparer=false);

int VGetInt(ZContextVar* v);
float VGetFloat(ZContextVar* v);
std::string VGetString(ZContextVar* v);
void* VGetC(ZContextVar* v);
ZClassNode* VGetClass(ZContextVar* v);