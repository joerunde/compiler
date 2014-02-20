#pragma once
#include "Token.h"
class BoolToken :
	public Token
{
public:
	BoolToken(std::string lexeme);
	~BoolToken(void);
	virtual std::string GetType();
	//virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

