#pragma once
#include "token.h"
class IDToken :
	public Token
{
public:
	IDToken(std::string lexeme);
	~IDToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

