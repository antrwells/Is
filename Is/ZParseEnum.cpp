#include "ZParseEnum.h"
#include "ZEnumNode.h"

ZParseEnum::ZParseEnum(ZTokenStream* stream) : ZParseNode(stream) {


}


ZScriptNode* ZParseEnum::Parse() {

	auto tok = mStream->NextToken();

	if (tok.mType == TokenType::TokenEndOfLine) {

		mStream->Back();
		mStream->Back();

		tok = mStream->NextToken();

	}

	//tok = mStream->NextToken();

	auto r = new ZEnumNode;

	r->SetName(tok.mText);

	while (!mStream->EOS())
	{

		tok = mStream->NextToken();
		switch (tok.mType) {
		case TokenType::TokenIdent:
			r->AddOption(tok.mText);
			break;
		case TokenType::TokenComma:
			break;
		case TokenType::TokenEnd:
			return r;
			break;
		}


	}

	return nullptr;

}