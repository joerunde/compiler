#pragma once
#include "Token.h"
class IDToken :
	public Token
{
public:
	IDToken(std::string lexeme);
	~IDToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isID();
	virtual int GetReturnType(int type);	
private:
	int mType;
};

