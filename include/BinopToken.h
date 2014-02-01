#pragma once
#include "token.h"
class BinopToken :
	public Token
{
public:
	BinopToken(std::string lexeme);
	~BinopToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);
};

