#include "../include/TypToken.h"


TypToken::TypToken(std::string lexeme):
	Token(lexeme)
{
}

TypToken::~TypToken(void)
{
}

std::string TypToken::GetType()
{
	return("Type");
}


Token* TypToken::GetToken(std::string lexeme)
{
	return new TypToken(lexeme);
}