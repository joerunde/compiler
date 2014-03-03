#pragma once
#include "Token.h"
class StrToken :
	public Token
{
public:
	StrToken(std::string lexeme);
	~StrToken(void);
	virtual std::string GetType();
	//virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isStr();
	virtual bool isConstant();

	virtual std::string GetLexeme(int type);
};

