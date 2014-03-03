#include "../include/StrToken.h"


StrToken::StrToken(std::string lexeme):
	Token(lexeme)
{
}


StrToken::~StrToken(void)
{
}

std::string StrToken::GetType()
{
	return("String");
}

Token* StrToken::GetToken(std::string lexeme)
{
	return new StrToken(lexeme);
}

bool StrToken::isStr()
{
	return true;
}

bool StrToken::isConstant()
{
	return true;
}

std::string StrToken::GetLexeme(int type)
{
	//start with gforth prefix
	std::string tmp = "s\" ";
	//append the string literal with first quotation stripped
	tmp.append(mLexeme.begin() + 1, mLexeme.end());

	return tmp;
}