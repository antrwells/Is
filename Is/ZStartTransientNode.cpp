#include "ZStartTransientNode.h"
#include "ZScriptContext.h"
#include "ZTransientNode.h"
#include "ZClassNode.h"
#include "ZMethodNode.h"
#include <thread>

void trans_thread(void* inst) {

	ZTransientNode* node = (ZTransientNode*)inst;

	while (true) {


		node->CallMethod("Update", {});

	}

}

void ZStartTransientNode::SetTransientName(std::string name) {

	mStartName = name;

}

ZContextVar* ZStartTransientNode::Exec(const std::vector<ZContextVar*>& params)
{

	int a = 5;

	auto trans = ZScriptContext::CurrentContext->GetTransient(mStartName);

	auto inst = trans->CreateInstance("Trans", {});

	inst->CallMethod("Start", {});

	std::thread t1(trans_thread,(void*)inst);
	t1.detach();
	
	return nullptr;
}