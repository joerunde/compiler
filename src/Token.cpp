#include "../include/Token.h"
#include <iostream>
#include "../include/SymbolTable.h"

SymbolTable* Token::sSymTable = 0;

Token::Token(std::string lexeme):
	mLexeme(lexeme)
{
}


Token::~Token()
{
}

std::string Token::GetLexeme()
{
	return mLexeme;
}

/*Automaton* Token::GetAutomaton()
{
	if(!mHasRegEx)
		std::cout << "Oh no! No Automaton!\n";
	return mRegEx;
}
*/
void Token::setSymbolTable(SymbolTable* table)
{
	sSymTable = table;
}