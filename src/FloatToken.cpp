#include "../include/FloatToken.h"


FloatToken::FloatToken(std::string lexeme):
	Token(lexeme)
{
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

