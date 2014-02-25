#include "../include/UnopToken.h"


UnopToken::UnopToken(std::string lexeme):
	Token(lexeme)
{
}

UnopToken::~UnopToken(void)
{
}

std::string UnopToken::GetType()
{
	return("Unop");
}

Token* UnopToken::GetToken(std::string lexeme)
{
	return new UnopToken(lexeme);
}

bool UnopToken::isUnop()
{
	return true;
}