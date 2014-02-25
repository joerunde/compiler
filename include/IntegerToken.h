#pragma once
#include "Token.h"
class IntegerToken :
	public Token
{
public:
	IntegerToken(std::string lexeme);
	~IntegerToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isConstant();
	virtual bool isInt();
};

