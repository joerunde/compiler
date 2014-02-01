#include "..\include\Token.h"
#include <iostream>

Token::Token(std::string lexeme):
	mLexeme(lexeme),
	mHasRegEx(false)
{
}


Token::~Token()
{
}

std::string Token::GetLexeme()
{
	return mLexeme;
}

Automaton* Token::GetAutomaton()
{
	if(!mHasRegEx)
		std::cout << "Oh no! No Automaton!\n";
	return mRegEx;
}