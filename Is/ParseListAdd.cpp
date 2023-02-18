#include "ParseListAdd.h"
#include "ZListAddNode.h"
#include "ZParseExpression.h"
#include "ZExpressionNode.h"
ZParseListAdd::ZParseListAdd(ZTokenStream* stream) : ZParseNode(stream)
{

}

ZScriptNode* ZParseListAdd::Parse()
{

	auto tok = mStream->NextToken();

	auto name = mStream->NextToken();

	auto node = new ZListAddNode;

	auto expr_parse = new ZParseExpression(mStream);
	auto expr = expr_parse->Parse();

	node->SetExpr((ZExpressionNode*)expr);
	node->SetName(name.mText);

	int a = 5;


	return node;
}