// IsTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ZClassNode.h>
#include "ZSource.h"
#include "ZParser.h"
#include "ZTokenizer.h"
#include "ZContextVar.h"
#include "ZProgramNode.h"
#include "ZScriptContext.h"
#include "ZSystemFunction.h"
#include "ZSystemFunctions.h"
ZContextVar* sys_console(const std::vector<ZContextVar*>& args)
{

	int a = 5;

	std::string out = "";

	for (int i = 0; i < args.size(); i++) {
		out = out + args[i]->GetStringVal() + " ";
	}

	printf(out.c_str());
	printf("\n");
	return nullptr;
}
int main()
{
	auto sc = new ZScriptContext;
	ZSystemFunction printf("console", sys_console);
	auto funcs = ZScriptContext::CurrentContext->GetSysFuncs();
	funcs->RegisterFunction(printf);
    std::cout << "Hello World!\n";
	auto src = new ZSource("script/test.zs");
	ZTokenizer* toker = new ZTokenizer(src);
	auto stream = toker->Tokenize();
	auto parser = new ZParser(stream);
	auto mNode = parser->Parse();
	ZScriptContext::CurrentContext->AddNode(mNode);

	//--
	auto ide_class = mNode->GetClass("IDE");

	auto ide_inst = ide_class->CreateInstance("IDEInst", {});


	ide_inst->CallMethod("InitIDE", {});
	
	int a = 5;



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
