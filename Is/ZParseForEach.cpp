#include "ZParseForEach.h"
#include <assert.h>
#include "ZParseCodeBody.h"
#include "ZForEachNode.h"
ZParseForEach::ZParseForEach(ZTokenStream* stream) : ZParseNode(stream) {


}

ZScriptNode* ZParseForEach::Parse() {


	auto tok = mStream->NextToken();

	if (tok.mType == TokenType::TokenEndOfLine) {
		tok = mStream->NextToken();
	}

	auto item_name = mStream->NextToken().mText;

	if (mStream->NextToken().mText != "in") {
	//	mStream->Error("Expected 'in' after for each item name");
		assert(0);
	}

	auto list_name = mStream->NextToken().mText;

	auto code_parse = new ZParseCodeBody(mStream);

	auto foreach_node = new ZForEachNode;

	foreach_node->SetNames(item_name, list_name);

	auto code_node = code_parse->Parse();


	foreach_node->SetBody((ZCodeBodyNode*)code_node);


	int a = 5;
	
	return foreach_node;
}