#include "../include/KeywordToken.h"


//std::set<std::string> KeywordToken::sKeywordSymbols = KeywordToken::sInitializeSymbols();

KeywordToken::KeywordToken(std::string lexeme):
	Token(lexeme)
{
}

KeywordToken::~KeywordToken(void)
{
}

std::string KeywordToken::GetType()
{
	return("Keyword");
}


Token* KeywordToken::GetToken(std::string lexeme)
{
	return new KeywordToken(lexeme);
}

