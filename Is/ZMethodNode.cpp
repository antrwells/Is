#include "ZMethodNode.h"
#include "ZSignatureNode.h"
#include "ZContextVar.h"
#include "ZCodeBodyNode.h"
#include "ZExpressionNode.h"
void ZMethodNode::SetName(std::string name)
{
	std::hash<std::string> hasher;
	mMethodName = name;
	mNameHash = hasher(name);

}

void ZMethodNode::SetSignature(ZSignatureNode* node)
{

	mSignature = node;

}

void ZMethodNode::SetReturnType(VarType type) {

	mReturnType = type;

}

void ZMethodNode::SetCode(ZCodeBodyNode* code)
{

	mCode = code;

}

std::string ZMethodNode::GetName() {

	return mMethodName;

}

ZContextVar* ZMethodNode::Exec(const std::vector<ZContextVar*>& params)
{	
	//mCode->SetClassOwner(
	mCode->SetClassOwner(GetClassOwner());

	if (mGuardExpr != nullptr) {

		if (mGuardExpr->Exec({})->GetIntVal()<=0) {
			return new ZContextVar("", VarType::VarInteger,"Zero",false);
		}

	}
	return mCode->Exec(params);
	//return nullptr;
}

void ZMethodNode::SetGuard(ZExpressionNode* g_e)
{
	mGuardExpr = g_e;
}

void ZMethodNode::SetScope(ZContextScope* scope) {

	mScope = scope;

}

ZContextScope* ZMethodNode::GetScope() {

	return mScope;

}

void ZMethodNode::Bind() {

	mCode->SetClassOwner(GetClassOwner());


}


void ZMethodNode::SetVirtual(bool is_virtual) {

	mIsVirtual = is_virtual;

}

bool ZMethodNode::GetVirtual() {

	return mIsVirtual;

}

ZMethodNode* ZMethodNode::mCurrentNode = nullptr;