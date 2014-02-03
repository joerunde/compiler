#include "../include/BinopToken.h"


BinopToken::BinopToken(std::string lexeme):
	Token(lexeme)
{
}


BinopToken::~BinopToken(void)
{
}

std::string BinopToken::GetType()
{
	return("Binop");
}

Token* BinopToken::GetToken(std::string lexeme)
{
	return new BinopToken(lexeme);
}

void BinopToken::SetupAutomata()
{
	tStateMap states;
	tTransitionMap transitions;
	std::set<int> acceptStates;

	states[0].insert('+');
	states[0].insert('-');
	states[0].insert('*');
	states[0].insert('/');
	states[0].insert('%');
	states[0].insert('^');
	states[0].insert('=');
	states[0].insert('<');
	states[0].insert('>');
	states[0].insert('!');
	transitions[0]['+'] = 1;
	transitions[0]['-'] = 1;
	transitions[0]['*'] = 1;
	transitions[0]['/'] = 1;
	transitions[0]['%'] = 1;
	transitions[0]['^'] = 1;
	transitions[0]['='] = 1;
	transitions[0]['<'] = 2;
	transitions[0]['>'] = 2;
	transitions[0]['!'] = 3;
	acceptStates.insert(1);
	acceptStates.insert(2);
	states[2].insert('=');
	transitions[2]['='] = 4; //4 is <=, >=, !=
	acceptStates.insert(4);
	states[3].insert('=');
	transitions[3]['='] = 4;

	//and, or
	states[0].insert('a');
	states[5].insert('n');
	states[6].insert('d');
	states[0].insert('o');
	states[8].insert('r');

	transitions[0]['a'] = 5;
	transitions[5]['n'] = 6;
	transitions[6]['d'] = 7;
	transitions[0]['o'] = 8;
	transitions[8]['r'] = 9;

	acceptStates.insert(7);
	acceptStates.insert(9);

	states[0].insert(':');
	states[10].insert('=');
	
	transitions[0][':'] = 10;
	transitions[10]['='] = 11;

	acceptStates.insert(11);


	mRegEx = new Automaton(states, transitions, acceptStates);
	mHasRegEx = true;
}
