#include "../include/BoolToken.h"


BoolToken::BoolToken(std::string lexeme):
	Token(lexeme)
{
}


BoolToken::~BoolToken(void)
{
}

std::string BoolToken::GetType()
{
	return("Bool");
}

Token* BoolToken::GetToken(std::string lexeme)
{
	return new BoolToken(lexeme);
}

void BoolToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	states[0].insert('t');
	states[0].insert('r');
	states[0].insert('u');
	states[0].insert('e');
	states[0].insert('f');
	states[0].insert('a');
	states[0].insert('l');
	states[0].insert('s');
	states[0].insert('e');

	transitions[0]['t'] = 1;
	transitions[1]['r'] = 2;
	transitions[2]['u'] = 3;
	transitions[3]['e'] = 4;
	transitions[0]['f'] = 5;
	transitions[5]['a'] = 6;
	transitions[6]['l'] = 7;
	transitions[7]['s'] = 8;
	transitions[8]['e'] = 9;

	acceptStates.insert(4);
	acceptStates.insert(9);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
