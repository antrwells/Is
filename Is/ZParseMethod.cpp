#include "ZParseMethod.h"
#include "ZMethodNode.h"
#include "ZParseSignature.h"
#include "ZSignatureNode.h"
#include "ZParseCodeBody.h"
#include "ZCodeBodyNode.h"
#include "ZParseExpression.h"
#include "ZExpressionNode.h"
#include "ZParseMethod.h"

ZParseMethod::ZParseMethod(ZTokenStream* stream) : ZParseNode(stream)
{

}



ZScriptNode* ZParseMethod::Parse()
{


	//Error("Error Parsing method.");



	
	auto meth_node = new ZMethodNode;

	ZMethodNode::mCurrentNode = meth_node;

	bool is_virtual = false;
	auto return_type = mStream->NextToken();

	if (return_type.mType == TokenType::TokenVirtual)
	{
		is_virtual = true;
		return_type = mStream->NextToken();
	}
	

	switch (return_type.mType) {
	case TokenType::TokenInt:
		meth_node->SetReturnType(VarType::VarInteger);
		break;
	case TokenType::TokenFloat:
		meth_node->SetReturnType(VarType::VarFloat);
		break;
	case TokenType::TokenString:
		meth_node->SetReturnType(VarType::VarString);
		break;
	case TokenType::TokenVoid:
		meth_node->SetReturnType(VarType::VarVoid);
	case TokenType::TokenBool:
		meth_node->SetReturnType(VarType::VarBool);
		break;
	case TokenType::TokenVar:
		meth_node->SetReturnType(VarType::VarVar);
		break;
	}

	int bb = 5;

	auto meth_name = mStream->NextToken();

	if (meth_name.mType == TokenType::TokenLeftPara)
	{

		mStream->Back();
		mStream->Back();
		meth_name = mStream->NextToken();

	}

	meth_node->SetName(meth_name.mText);

	auto parse_sig = new ZParseSignature(mStream);

	auto sig_node = (ZSignatureNode*)parse_sig->Parse();
	
	meth_node->SetSignature(sig_node);

	mStream->Back();

	auto next_tok = mStream->NextToken();

	if (next_tok.mType == TokenType::TokenRightPara)
	{

		//next_tok=mStream->NextToken();

	}

	auto nn = mStream->PeekToken(0);

	if (nn.mType == TokenType::TokenColon)
	{

		mStream->NextToken();
		auto g_ex = new ZParseExpression(mStream);
		auto g_n = (ZExpressionNode*)g_ex->Parse();

		meth_node->SetGuard(g_n);
	}

//	next_tok = mStream->NextToken();
	//next_tok = mStream->NextToken();


	auto code_parse = new ZParseCodeBody(mStream);

	if (mStream->PeekToken(0).mType == TokenType::TokenEndOfLine) {
		mStream->NextToken();
	}

	auto code_node = (ZCodeBodyNode*)code_parse->Parse();

	code_node->SetOwner(meth_node);

	meth_node->SetCode(code_node);

	meth_node->SetVirtual(is_virtual);

	int aa = 5;

	return meth_node;
}