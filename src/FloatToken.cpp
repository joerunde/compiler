#include "../include/FloatToken.h"


FloatToken::FloatToken(std::string lexeme):
	Token(lexeme)
{
	//append an "e0" if there's no e in the number
	if(mLexeme.find("e") == std::string::npos)
	{
		mLexeme.append("e0");
	}
}


FloatToken::~FloatToken(void)
{
}

std::string FloatToken::GetType()
{
	return("Real");
}

Token* FloatToken::GetToken(std::string lexeme )
{
	return new FloatToken(lexeme);
}

bool FloatToken::isConstant()
{
	return true;
}

bool FloatToken::isReal()
{
	return true;
}