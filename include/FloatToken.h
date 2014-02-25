#pragma once
#include "Token.h"
class FloatToken :
	public Token
{
public:
	FloatToken(std::string lexeme);
	~FloatToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isConstant();
	virtual bool isReal();
};

