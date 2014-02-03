#pragma once
#include "Token.h"
class StrToken :
	public Token
{
public:
	StrToken(std::string lexeme);
	~StrToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

