#pragma once
#include "Token.h"

class KeywordToken :
	public Token
{
public:
	KeywordToken(std::string lexeme);
	~KeywordToken(void);
	virtual std::string GetType();
	virtual Token* GetToken(std::string lexeme);
	virtual bool isKeyword();
	virtual bool isWhile();
	virtual bool isIf();
	virtual bool isLet();
	virtual bool isStdout();

};

