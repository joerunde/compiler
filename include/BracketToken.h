#pragma once
#include "Token.h"
class BracketToken :
	public Token
{
public:
	BracketToken(std::string lexeme);
	~BracketToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

