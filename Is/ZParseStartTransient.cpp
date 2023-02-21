#include "ZParseStartTransient.h"
#include "ZStartTransientNode.h"
//
// ZParseStartTransient.cpp
//
ZParseStartTransient::ZParseStartTransient(ZTokenStream* stream) : ZParseNode(stream)
{

}

ZScriptNode* ZParseStartTransient::Parse()
{
	
	auto tok = mStream->NextToken();

	if (tok.mType == TokenType::TokenStartTransient)
	{
		tok = mStream->NextToken();
	}


	ZStartTransientNode* node = new ZStartTransientNode;

	node->SetTransientName(tok.mText);

	return node;
}

