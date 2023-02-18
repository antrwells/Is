#include "ZContextVar.h"
//#include "ZClassNode.h"

#include "VarTypes.h"
#include "ZClassNode.h"

ZContextVar::ZContextVar(std::string name, enum VarType type,std::string baseID,bool comparer) {
	
	std::hash<std::string> hasher;

	
	mHashName = hasher(name);

	mName = name;
	mType = type;
	mIntVal = 0;
	mFloatVal = 0;
	mStringVal = "";
	mClassVal = nullptr;
	mBaseID = baseID;
	mComparer = comparer;
}

std::string ZContextVar::GetName() {

	return mName;

}

size_t ZContextVar::GetHashName() {

	return mHashName;

}

VarType ZContextVar::GetType() {

	return mType;

}
bool ZContextVar::GetBoolVal() {

	{
		if (mType == VarType::VarInteger) {
		return mIntVal != 0;
	}
		if (mType == VarType::VarFloat) {
		return mFloatVal != 0;
	}
		if (mType == VarType::VarString) {
		return mStringVal != "";
	}
		if (mType == VarType::VarClass) {
		return mClassVal != nullptr;
	}
		return mBoolVal;
}

}

void ZContextVar::SetBool(bool v) {

	if (mType == VarType::VarInteger)
	{
		if (v) { mIntVal = 1; }
		else
		{
			mIntVal = 0;
		}
		return;
	}

	if (mType == VarType::VarFloat) {

		if (v) {
			mFloatVal = 1;
		}
		else {
			mFloatVal = 0;
		}
		return;
	}
	
	if (mType == VarType::VarString) {

		if (v)
		{
			mStringVal = "true";
		}
		else {
			mStringVal = "false";
		}
		return;
	}

	{
		mBoolVal = v;
	}

}

int ZContextVar::GetIntVal() {

	if (mType == VarType::VarFloat)
	{
		return (int)mFloatVal;
	}
	if (mType == VarType::VarBool) {

		if (mBoolVal) {
			return 1;
		}
		else {
			return 0;
		}

	}
	return mIntVal;

}

float ZContextVar::GetFloatVal() {

	if (mType == VarType::VarInteger)
	{
		return (float)mIntVal;
	}
	if (mType == VarType::VarBool) {

		if (mBoolVal) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return mFloatVal;

}

std::string ZContextVar::GetStringVal() {

	if (mType == VarType::VarInteger) {
		return std::to_string(mIntVal);
	}
	if (mType == VarType::VarFloat) {
		return std::to_string(mFloatVal);
	}
	if (mType == VarType::VarBool) {
		int v = 1;
		if (mBoolVal == false)
		{
			v = 0;
		}
		return std::to_string(v);
	}
	return mStringVal;

}


ZClassNode* ZContextVar::GetClassVal()
{

	return mClassVal;

}

void ZContextVar::SetInt(int val) {

	if (mType == VarType::VarFloat) {
		mFloatVal = (float)val;
	}
	mIntVal = val;
	mCurrentType = VarInteger;

}

void ZContextVar::SetFloat(float val) {

	if (mType == VarType::VarInteger)
	{
		mIntVal = (int)val;
	}
	mFloatVal = val;
	mCurrentType = VarFloat;

}

void ZContextVar::SetString(std::string val)
{

	mStringVal = val;
	mCurrentType = VarString;

}

void ZContextVar::SetClass(ZClassNode* cls) {

	mClassVal = cls;
	mCurrentType = VarInstance;

}

void* ZContextVar::GetCObj() {

	return mCObj;

}

void ZContextVar::SetCObj(void * obj) {

	mCObj = obj;

}

void ZContextVar::Push() {

	switch (mType)
	{
	case VarType::VarBool:
		mPushBool = mBoolVal;
		break;
	case VarType::VarFloat:
		mPushFloat = mFloatVal;
		break;
	case VarType::VarInteger:
		mPushInt = mIntVal;
		break;
	case VarType::VarInstance:

	{
		auto vc = mClassVal;
		if (vc == nullptr) return;
		auto vars = vc->GetVars();
		for (int i = 0; i < vars.size(); i++)
		{
			auto v = vars[i];
			v->Push();
		}
	}
		break;
	case VarType::VarString:
		mPushString = mStringVal;
		break;
	case VarType::VarList:
		for (int i = 0; i < mList.size(); i++) {
			mList[i]->Push();
		}
		break;
	}

		

}

void ZContextVar::Pop() {

	switch (mType) {
	case VarType::VarBool:
		mBoolVal = mPushBool;
		break;
	case VarType::VarFloat:

		mFloatVal = mPushFloat;

		break;
	case VarType::VarInteger:
		mIntVal = mPushInt;
		break;
	case VarType::VarInstance:
	{
		auto vc = mClassVal;
		if (vc == nullptr) return;
		auto vars = vc->GetVars();
		for (int i = 0; i < vars.size(); i++)
		{
			auto v = vars[i];
			v->Pop();
		}
	}	break;
	case VarType::VarString:
		mStringVal = mPushString;
		break;
	case VarType::VarList:
		for (int i = 0; i < mList.size(); i++) {
			mList[i]->Pop();
		}
		break;
	}

}

void ZContextVar::ListAdd(ZContextVar* v) {

	mList.push_back(v);

}



ZContextVar* VMakeInt(int v,bool comparer)
{
	auto var = new ZContextVar("", VarType::VarInteger,"int",comparer);
	var->SetInt(v);


	return var;

}
ZContextVar* VMakeFloat(float v,bool comparer)
{
	auto var = new ZContextVar("", VarType::VarFloat,"float",comparer);
	var->SetFloat(v);

	return var;

}

ZContextVar* VMakeString(std::string v,bool comparer)
{
	auto var = new ZContextVar("", VarType::VarString,"string",comparer);
	var->SetString(v);

	return var;

}

ZContextVar* VMakeC(void* v,bool comparer)
{
	auto var = new ZContextVar("", VarType::VarCObj,"CObj",comparer);
	var->SetCObj(v);

	return var;

}

ZContextVar* VMakeClass(ZClassNode* v,bool comparer)
{

	auto var = new ZContextVar("", VarType::VarInstance,v->GetBaseName(),comparer);
	var->SetClass(v);

	return var;

}

int VGetInt(ZContextVar* v)
{
	return v->GetIntVal();
}

float VGetFloat(ZContextVar* v)
{
	return v->GetFloatVal();
}

std::string VGetString(ZContextVar* v)
{
	return v->GetStringVal();
}

ZClassNode* VGetClass(ZContextVar* v)
{
	return v->GetClassVal();
}

void* VGetC(ZContextVar* v)
{
	return v->GetCObj();
}


