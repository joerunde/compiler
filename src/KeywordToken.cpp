#include "../include/KeywordToken.h"

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

bool KeywordToken::isKeyword()
{
	return true;
}

bool KeywordToken::isIf()
{
	if(mLexeme == "if")
		return true;
	return false;
}

bool KeywordToken::isWhile()
{
	if(mLexeme == "while")
		return true;
	return false;
}

bool KeywordToken::isLet()
{
	if(mLexeme == "let")
		return true;
	return false;
}

bool KeywordToken::isStdout()
{
	if(mLexeme == "stdout")
		return true;
	return false;
}

std::string KeywordToken::GetLexeme(int type)
{
	if(isLet())
	{
		return "";
	}
	return mLexeme;
}