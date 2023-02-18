#pragma once
#include "ZTokenStream.h"
#include <vector>
#include <string>
#include "ZSource.h"
#include <iostream>

class ZTokenizer
{
public:

	ZTokenizer(ZSource * source);
	ZTokenizer(std::string code);
	ZTokenStream* Tokenize();
	ZTokens* Finalize(ZTokenStream* stream);

private:

	std::vector<std::string> mCode;

};

