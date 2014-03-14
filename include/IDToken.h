#pragma once
#include "Token.h"
class IDToken :
	public Token
{
public:
	IDToken(std::string lexeme);
	~IDToken(void);
	virtual std::string GetType();
	virtual std::string GetLexeme(int type);
	virtual Token* GetToken(std::string lexeme);
	virtual bool isID();
	virtual int GetReturnType(int type);
	void setType(int type);
private:
	int mType;
};

