#include "../include/BracketToken.h"


BracketToken::BracketToken(std::string lexeme):
	Token(lexeme)
{
}


BracketToken::~BracketToken(void)
{
}

std::string BracketToken::GetType()
{
	return("Bracket");
}

Token* BracketToken::GetToken(std::string lexeme)
{
	return new BracketToken(lexeme);
}

void BracketToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	states[0].insert('[');
	states[0].insert(']');
	transitions[0]['['] = 1;
	transitions[0][']'] = 1;
	acceptStates.insert(1);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
