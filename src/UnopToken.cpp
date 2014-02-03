#include "../include/UnopToken.h"


UnopToken::UnopToken(std::string lexeme):
	Token(lexeme)
{
}


UnopToken::~UnopToken(void)
{
}

std::string UnopToken::GetType()
{
	return("Unop");
}

Token* UnopToken::GetToken(std::string lexeme)
{
	return new UnopToken(lexeme);
}

void UnopToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	//states[0].insert('-');
	//transitions[0]['-'] = 1;
	//acceptStates.insert(1);

	states[0].insert('s');
	states[2].insert('i');
	states[3].insert('n');

	transitions[0]['s'] = 2;
	transitions[2]['i'] = 3;
	transitions[3]['n'] = 4;

	acceptStates.insert(4);

	states[0].insert('c');
	states[5].insert('o');
	states[6].insert('s');

	transitions[0]['c'] = 5;
	transitions[5]['o'] = 6;
	transitions[6]['s'] = 7;

	acceptStates.insert(7);

	states[0].insert('t');
	states[8].insert('a');
	states[9].insert('n');

	transitions[0]['t'] = 8;
	transitions[8]['a'] = 9;
	transitions[9]['n'] = 10;

	acceptStates.insert(10);

	states[0].insert('n');
	states[11].insert('o');
	states[12].insert('t');

	transitions[0]['n'] = 11;
	transitions[11]['o'] = 12;
	transitions[12]['t'] = 13;

	acceptStates.insert(13);

	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
