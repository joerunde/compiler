#include "..\include\KeywordToken.h"


std::set<std::string> KeywordToken::sKeywordSymbols = KeywordToken::sInitializeSymbols();

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

void KeywordToken::SetupAutomata()
{
	//we'll do something different
}

Token* KeywordToken::GetToken(std::string lexeme)
{
	return new KeywordToken(lexeme);
}

std::set<std::string> KeywordToken::sInitializeSymbols()
{
	std::set<std::string> symbols;
	symbols.insert("while");
	symbols.insert("for");
	symbols.insert("if");
	symbols.insert("let");
	symbols.insert("stdout");
	return symbols;
}

bool KeywordToken::sIsKeyword(std::string lexeme)
{
	int count = sKeywordSymbols.count(lexeme);
	return(count != 0);
}