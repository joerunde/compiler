#pragma once
#include "token.h"
class IntegerToken :
	public Token
{
public:
	IntegerToken(std::string lexeme);
	~IntegerToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

