#pragma once
#include "Token.h"
class BracketToken :
	public Token
{
public:
	BracketToken(std::string lexeme);
	~BracketToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isRB();
	virtual bool isLB();
};

