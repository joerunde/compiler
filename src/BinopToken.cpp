#include "../include/BinopToken.h"


BinopToken::BinopToken(std::string lexeme):
	Token(lexeme)
{
}


BinopToken::~BinopToken(void)
{
}

std::string BinopToken::GetType()
{
	return("Binop");
}

Token* BinopToken::GetToken(std::string lexeme)
{
	return new BinopToken(lexeme);
}

