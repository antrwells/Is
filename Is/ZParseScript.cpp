#include "ZParseScript.h"
#include "ZProgramNode.h"
#include "ZParseClass.h"
#include "ZParseEnum.h"
#include "ZEnumNode.h"
//#include


ZParseScript::ZParseScript(ZTokenStream* stream) : ZParseNode(stream) {

	//int aa = 5;


}

ZScriptNode* ZParseScript::Parse()
{

	ZMainNode* main_node = new ZMainNode;

 

	while (!mStream->EOS())
	{

		auto token = mStream->NextToken();

		switch (token.mType) {
		case TokenType::EndOfFile:

			return (ZScriptNode*)main_node;

			break;
		case TokenType::TokenEnum:
		{

			mStream->NextToken();

			auto parse_enum = new ZParseEnum(mStream);
			auto enum_node = parse_enum->Parse();

			main_node->AddEnum((ZEnumNode*)enum_node);

		}
			break;
		case TokenType::TokenStatic:
		{

			mStream->NextToken();

			auto parse_class = new ZParseClass(mStream);

			auto class_node = (ZClassNode*)parse_class->Parse();

			main_node->AddStaticClass(class_node);
			int aa = 5;
		}

			break;
		case TokenType::TokenClass:


			auto parse_class = new ZParseClass(mStream);
			
			auto class_node = (ZClassNode*) parse_class->Parse();

			main_node->AddClass(class_node);
			
			int aa = 5;
			
			break;

		}

		//int aa = 5;


	}

	return (ZScriptNode*)main_node;

}