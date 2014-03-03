#pragma once
#include "Token.h"
class UnopToken :
	public Token
{
public:
	UnopToken(std::string lexeme);
	~UnopToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isUnop();

	virtual std::string GetLexeme(int type);
};

