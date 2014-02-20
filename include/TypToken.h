#pragma once
#include "token.h"
class TypToken :
	public Token
{
public:
	TypToken(std::string lexeme);
	~TypToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
};

