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

