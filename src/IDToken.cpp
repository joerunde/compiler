#include "../include/IDToken.h"
#include "../include/KeywordToken.h"

IDToken::IDToken(std::string lexeme):
	Token(lexeme)
{
}


IDToken::~IDToken(void)
{
}

std::string IDToken::GetType()
{
	return("Identifier");
}

Token* IDToken::GetToken(std::string lexeme)
{
	if(KeywordToken::sIsKeyword(lexeme))
	{
		return new KeywordToken(lexeme);
	}
	return new IDToken(lexeme);
}

void IDToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	for(char c = 'a'; c <= 'z'; c++)
	{
		states[0].insert(c);
		states[1].insert(c);
		transitions[0][c] = 1;
	}
	for(char c = 'A'; c <= 'Z'; c++)
	{
		states[0].insert(c);
		states[1].insert(c);
		transitions[0][c] = 1;
	}
	for(char c = '0'; c <= '9'; c++)
	{
		states[1].insert(c);
	}
	
	acceptStates.insert(1);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
