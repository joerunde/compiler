#pragma once
#include "Token.h"

class KeywordToken :
	public Token
{
public:
	KeywordToken(std::string lexeme);
	~KeywordToken(void);
	virtual std::string GetType();
	virtual void SetupAutomata();
	virtual Token* GetToken(std::string lexeme);

	static bool sIsKeyword(std::string lexeme);
	
private:
	static std::set<std::string> sKeywordSymbols;
	static std::set<std::string> sInitializeSymbols();
};

