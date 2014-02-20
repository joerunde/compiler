#include "../include/IntegerToken.h"


IntegerToken::IntegerToken(std::string lexeme):
	Token(lexeme)
{
}


IntegerToken::~IntegerToken(void)
{
}

std::string IntegerToken::GetType()
{
	return("Int");
}

Token* IntegerToken::GetToken(std::string lexeme)
{
	return new IntegerToken(lexeme);
}


