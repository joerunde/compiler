#pragma once

#include <string>
#include "Automaton.h"

class Token
{
public:
	Token(std::string lexeme);
	~Token();

	virtual std::string GetType() = 0;
	std::string GetLexeme();

	virtual void SetupAutomata() = 0;
	virtual Token* GetToken(std::string lexeme) = 0;
	Automaton* GetAutomaton();

protected:
	std::string mToken;
	std::string mLexeme;

	Automaton* mRegEx;
	bool mHasRegEx;
};

