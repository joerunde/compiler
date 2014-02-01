#pragma once
#include "token.h"
class FloatToken :
	public Token
{
public:
	FloatToken(std::string lexeme);
	~FloatToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

