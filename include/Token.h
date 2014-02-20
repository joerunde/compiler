#pragma once

#include <string>
//#include "Automaton.h"

class SymbolTable;

class Token
{
public:
	Token(std::string lexeme);
	~Token();

	virtual std::string GetType() = 0;
	std::string GetLexeme();

	virtual Token* GetToken(std::string lexeme) = 0;

	static void setSymbolTable(SymbolTable* table);

protected:
	std::string mToken;
	std::string mLexeme;

	static SymbolTable* sSymTable;


};

