#include "..\include\IntegerToken.h"


IntegerToken::IntegerToken(std::string lexeme):
	Token(lexeme)
{
}


IntegerToken::~IntegerToken(void)
{
}

std::string IntegerToken::GetType()
{
	return("Int");
}

Token* IntegerToken::GetToken(std::string lexeme)
{
	return new IntegerToken(lexeme);
}

void IntegerToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	for(char c = '0'; c <= '9'; c++)
	{
		states[0].insert(c);
		states[1].insert(c);
		transitions[0][c] = 1;
	}
	acceptStates.insert(1);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}