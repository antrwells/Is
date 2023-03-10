#include "ZParseClass.h"
#include "ZClassNode.h"
#include "ZParseMethod.h"
#include "ZMethodNode.h"
#include "ZParseVars.h"
#include "ZVarsNode.h"

ZParseClass::ZParseClass(ZTokenStream* stream) : ZParseNode(stream)
{

}

ZScriptNode* ZParseClass::Parse()
{

	auto class_node = new ZClassNode;

	auto class_name = mStream->NextToken();
	auto class_ext = std::string("");

	if (mStream->PeekToken(0).mType == TokenType::TokenGreater)
	{
		mStream->NextToken();
		auto ext = mStream->NextToken();
		class_node->SetExtends(ext.mText);
		int bb = 5;
	}
	else {
		mStream->AssertNextToken(TokenType::TokenEndOfLine);
	}
	class_node->SetName(class_name.mText);

	while (!mStream->EOS()) {

		auto token = mStream->NextToken();

		//
		ZParseMethod* parse_meth;
		ZMethodNode* meth_node;
		ZParseVars* parse_vars;
		ZVarsNode* vars_node;
		//

		switch (token.mType) {
		case TokenType::TokenList:

			mStream->Back();
			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();

			//codebody->AddNode(vars_node);
			class_node->AddVars(vars_node);

			break;
		case TokenType::TokenIdent:

			mStream->Back();
			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();

			//codebody->AddNode(vars_node);
			class_node->AddVars(vars_node);

			//tk = mStream->NextToken();
			//vars_node->SetCodeOwner(codebody);

			break;
		case TokenType::TokenString:
		
		{
			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			class_node->AddVars(vars_node);
		}
			break;
		case TokenType::TokenBool:
		{

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			class_node->AddVars(vars_node);

		}

			break;
		case TokenType::TokenExpr:

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			class_node->AddVars(vars_node);

			break;
		case TokenType::TokenInt:
		case TokenType::TokenFloat:
	
		case TokenType::TokenCObj:

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			class_node->AddVars(vars_node);
//		mStream->Back();

			break;
		case TokenType::TokenEnd:
			

			if (!mStream->EOS()) {
				//mStream->Back();
				class_node->SetLineEnd(mStream->NextToken().TokenLineIndex);
				mStream->Back();
				mStream->AssertNextToken(TokenType::TokenEndOfLine);
			}
			else {
			
				mStream->Back();
				class_node->SetLineEnd(mStream->NextToken().TokenLineIndex);
			}
			
			return class_node;

			break;
		case TokenType::TokenMethod:

			parse_meth = new ZParseMethod(mStream);

			meth_node = (ZMethodNode*)parse_meth->Parse();
		
			class_node->AddMethod(meth_node);

			if (mStream->PeekToken(0).mType == TokenType::TokenEnd) {
				mStream->NextToken();
			}

			break;
		case TokenType::TokenFunction:

			break;
		}

	}

	class_node->mClass = class_node;

	return class_node;

}