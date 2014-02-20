#include "../include/BoolToken.h"


BoolToken::BoolToken(std::string lexeme):
	Token(lexeme)
{
}


BoolToken::~BoolToken(void)
{
}

std::string BoolToken::GetType()
{
	return("Bool");
}

Token* BoolToken::GetToken(std::string lexeme)
{
	return new BoolToken(lexeme);
}

