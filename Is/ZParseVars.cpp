#include "ZParseVars.h"
#include "ZVarsNode.h"
#include "ZExpressionNode.h"
#include "ZParseExpression.h"
#include "ZParseNew.h"

ZParseVars::ZParseVars(ZTokenStream* stream) : ZParseNode(stream) {

}

ZScriptNode* ZParseVars::Parse() {

	auto var_type = mStream->NextToken();



	auto vars_node = new ZVarsNode;
	bool is_class = false;
	switch (var_type.mType)
	{
	case TokenType::TokenMem:
		vars_node->SetType(VarType::VarMem);
		break;
	case TokenType::TokenList:
		vars_node->SetType(VarType::VarList);
		break;
	case TokenType::TokenBool:
		vars_node->SetType(VarType::VarBool);
		break;
	case TokenType::TokenInt:
		vars_node->SetType(VarType::VarInteger);
		break;
	case TokenType::TokenFloat:
		vars_node->SetType(VarType::VarFloat);
		break;
	case TokenType::TokenString:
		vars_node->SetType(VarType::VarString);
		break;
	case TokenType::TokenIdent:
		vars_node->SetType(VarType::VarInstance);
		vars_node->SetBaseType(var_type.mText);
		is_class = true;
		break;
	case TokenType::TokenCObj:
		vars_node->SetType(VarType::VarCObj);
		break;
	case TokenType::TokenVar:
		vars_node->SetType(VarType::VarVar);
		break;
	case TokenType::TokenExpr:
		vars_node->SetType(VarType::VarExpr);
		break;
	}

	while (!mStream->EOS()) {

		auto tok = mStream->NextToken();

		if (tok.mType == TokenType::TokenRightArray)
		{

			continue;
		}

		bool comparer = false;
		if (tok.mType == TokenType::TokenLeftPara) {

			if (mStream->PeekToken(1).mType == TokenType::TokenRightPara)
			{
				comparer = true;
				tok = mStream->NextToken();
				mStream->NextToken();
			}

		}

		auto def = new ZExpressionNode;


	
		if (tok.mType == TokenType::TokenEndOfLine)
		{
			return vars_node;
		}
		if (tok.mType == TokenType::TokenComma)
		{
			continue;
		}
		if (tok.mType == TokenType::TokenEquals)
		{

			

		}
		else {

			if (is_class) {


				if (mStream->FindInLine(TokenType::TokenNew))
				{
					if (mStream->Before(TokenType::TokenLeftPara, TokenType::TokenNew))
					{
						goto skip2;
					}
					else {
						auto parse_new = new ZParseNew(mStream);
						auto parse_node = parse_new->Parse();

						vars_node->AddVar(tok.mText, (ZNewNode*)parse_node,comparer);
					}
					continue;
				}
				else {
					skip2:

					auto check = mStream->PeekToken(0);
					if (check.mType == TokenType::TokenEndOfLine) {
						vars_node->AddVar(tok.mText,comparer);
						continue;
					}
					int cc = 1;
					auto exp_parse = new ZParseExpression(mStream);
					def = (ZExpressionNode*)exp_parse->Parse();
					int b = 5;
					vars_node->AddVar(tok.mText, def,comparer);

				}
				continue;
				


				int cc = 1;
			}
			else {
				if (mStream->PeekToken(0).mType == TokenType::TokenEquals) {
					int cc = 1;
					auto exp_parse = new ZParseExpression(mStream);
					def = (ZExpressionNode*)exp_parse->Parse();
					int b = 5;
				}
			}
			if (def->GetExpression().mElements.size() == 0)
			{
				def = nullptr;
			}
		
			//mStream->Back();
			auto ntok = mStream->PeekToken(0);
			
			bool isArray = false;
			if (ntok.mType == TokenType::TokenLeftArray)
			{
				mStream->NextToken();
				auto exp_parse = new ZParseExpression(mStream);
				def = (ZExpressionNode*)exp_parse->Parse();
				int aa = 5;
				isArray = true;
			}

			vars_node->AddVar(tok.mText,def,comparer);
			if (isArray) {
				vars_node->SetToArray();
			}

		}
		int aa = 5;

	}

	//int b = 5;


	return nullptr;
}