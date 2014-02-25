#pragma once
#include "Token.h"
class BinopToken :
	public Token
{
public:
	BinopToken(std::string lexeme);
	~BinopToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isBinop();
};

