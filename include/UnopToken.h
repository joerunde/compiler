#pragma once
#include "token.h"
class UnopToken :
	public Token
{
public:
	UnopToken(std::string lexeme);
	~UnopToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

