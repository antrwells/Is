#include "ZParseScript.h"
#include "ZProgramNode.h"
#include "ZParseClass.h"
#include "ZParseEnum.h"
#include "ZEnumNode.h"
#include "ZClassNode.h"
#include "ZParseTransient.h"
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

		{
			auto parse_class = new ZParseClass(mStream);

			int line_start = mStream->PeekToken(0).TokenLineIndex;

			auto class_node = (ZClassNode*)parse_class->Parse();

			class_node->SetLineStart(line_start);

			main_node->AddClass(class_node);

			int aa = 5;
		}
			break;
		case TokenType::TokenTransient:
		{
			auto parse_trans = new ZParseTransient(mStream);
			int line_start = mStream->PeekToken(0).TokenLineIndex;

			auto trans_node = parse_trans->Parse();

			main_node->AddTransient((ZTransientNode*)trans_node);

		}

			break;
		}

		//int aa = 5;


	}

	return (ZScriptNode*)main_node;

}