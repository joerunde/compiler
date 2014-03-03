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
	virtual std::string GetLexeme(int type);

	virtual Token* GetToken(std::string lexeme) = 0;

	virtual int GetReturnType(int type);

	static void setSymbolTable(SymbolTable* table);

	// reporting functions to figure out what kind of token you have

	virtual bool isRB();
	virtual bool isLB();
	virtual bool isConstant();
	virtual bool isInt();
	virtual bool isID();
	virtual bool isReal();
	virtual bool isBool();
	virtual bool isStr();
	virtual bool isAssign();
	virtual bool isUnop();
	virtual bool isBinop();
	
	virtual bool isTyp();
	virtual bool isKeyword();
	virtual bool isWhile();
	virtual bool isLet();
	virtual bool isIf();
	virtual bool isStdout();

protected:
	std::string mToken;
	std::string mLexeme;

	static SymbolTable* sSymTable;


};

class BlankToken: public Token
{
public:
	BlankToken() : Token(""){}
	virtual std::string GetType() {return "";}
	virtual Token* GetToken(std::string lexeme){return 0;}
};

