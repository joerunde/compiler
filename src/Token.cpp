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

void Token::setSymbolTable(SymbolTable* table)
{
	sSymTable = table;
}

bool Token::isRB()
{
	return false;
}
bool Token::isLB()
{
	return false;
}
bool Token::isConstant()
{
	return false;
}
bool Token::isInt()
{
	return false;
}
bool Token::isID()
{
	return false;
}
bool Token::isReal()
{
	return false;
}
bool Token::isBool()
{
	return false;
}
bool Token::isStr()
{
	return false;
}
bool Token::isAssign()
{
	return false;
}
bool Token::isUnop()
{
	return false;
}
bool Token::isBinop()
{
	return false;
}
	
bool Token::isTyp()
{
	return false;
}
bool Token::isKeyword()
{
	return false;
}
bool Token::isWhile()
{
	return false;
}
bool Token::isLet()
{
	return false;
}
bool Token::isIf()
{
	return false;
}
bool Token::isStdout()
{
	return false;
}