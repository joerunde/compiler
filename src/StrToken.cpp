#include "../include/StrToken.h"


StrToken::StrToken(std::string lexeme):
	Token(lexeme)
{
}


StrToken::~StrToken(void)
{
}

std::string StrToken::GetType()
{
	return("String");
}

Token* StrToken::GetToken(std::string lexeme)
{
	return new StrToken(lexeme);
}

void StrToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	states[0].insert('"');
	transitions[0]['"'] = 1;
	for(int c = 0; c < 256; c++)
	{
		states[1].insert(char(c));
	}
	transitions[1]['"'] = 2;
	acceptStates.insert(2);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
