#include "ZParseTransient.h"
#include "ZTransientNode.h"
#include "ZClassNode.h"
#include "ZParseMethod.h"
#include "ZMethodNode.h"
#include "ZParseVars.h"
#include "ZVarsNode.h"
ZParseTransient::ZParseTransient(ZTokenStream* stream) : ZParseNode(stream)
{

}

ZScriptNode* ZParseTransient::Parse()
{
	auto token = mStream->NextToken();

	auto trans_node = new ZTransientNode;

	trans_node->SetName(token.mText);

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
			trans_node->AddVars(vars_node);

			break;
		case TokenType::TokenIdent:

			mStream->Back();
			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();

			//codebody->AddNode(vars_node);
			trans_node->AddVars(vars_node);

			//tk = mStream->NextToken();
			//vars_node->SetCodeOwner(codebody);

			break;
		case TokenType::TokenString:

		{
			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			trans_node->AddVars(vars_node);
		}
		break;
		case TokenType::TokenBool:
		{

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			trans_node->AddVars(vars_node);

		}

		break;
		case TokenType::TokenExpr:

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			trans_node->AddVars(vars_node);

			break;
		case TokenType::TokenInt:
		case TokenType::TokenFloat:

		case TokenType::TokenCObj:

			mStream->Back();

			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();


			trans_node->AddVars(vars_node);
			//		mStream->Back();

			break;
		case TokenType::TokenEnd:


			if (!mStream->EOS()) {
				//mStream->Back();
				trans_node->SetLineEnd(mStream->NextToken().TokenLineIndex);
				mStream->Back();
				mStream->AssertNextToken(TokenType::TokenEndOfLine);
			}
			else {

				mStream->Back();
				trans_node->SetLineEnd(mStream->NextToken().TokenLineIndex);
			}

			return trans_node;

			break;
		case TokenType::TokenMethod:

			parse_meth = new ZParseMethod(mStream);

			meth_node = (ZMethodNode*)parse_meth->Parse();

			trans_node->AddMethod(meth_node);

			if (mStream->PeekToken(0).mType == TokenType::TokenEnd) {
				mStream->NextToken();
			}

			break;
		case TokenType::TokenFunction:

			break;
		}

	}


	int aa = 5;
	return nullptr;
}