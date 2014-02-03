#include "../include/FloatToken.h"


FloatToken::FloatToken(std::string lexeme):
	Token(lexeme)
{
}


FloatToken::~FloatToken(void)
{
}

std::string FloatToken::GetType()
{
	return("Real");
}

Token* FloatToken::GetToken(std::string lexeme)
{
	return new FloatToken(lexeme);
}

void FloatToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	for(char c = '0'; c <= '9'; c++)
	{
		states[0].insert(c);
		states[1].insert(c);
	}
	states[0].insert('.');
	transitions[0]['.'] = 1;
	acceptStates.insert(1);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
