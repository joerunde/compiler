#include "../include/BracketToken.h"


BracketToken::BracketToken(std::string lexeme):
	Token(lexeme)
{
}


BracketToken::~BracketToken(void)
{
}

std::string BracketToken::GetType()
{
	return("Bracket");
}

Token* BracketToken::GetToken(std::string lexeme)
{
	return new BracketToken(lexeme);
}


