#pragma once

#include <set>
#include <map>

/* 
	Class defining a deterministic finite automaton.
*/



typedef std::map<int, std::set<char> > tStateMap;
typedef std::map<int, std::map<char, int> > tTransitionMap;

class Automaton
{
public:
	//By convention, 0 is the starting state. After that put in any positive int for the state numbers.
	//If a character exists for a state in the state map, but does NOT exists in the transition map
	//for that state, it is assumed that a transition exists that loops back to the same state.
	Automaton(tStateMap states, tTransitionMap transitions, std::set<int> acceptStates);
	~Automaton();

	enum eOutput{
		YES,		//Currently in an accept state
		NO,			//Currently in an error state
		NO_BUT_WAS,	//Was in an accept state, then errored
		MAYBE,		//Not in an accept or error state
	};

	//reset internal state to the starting state
	void ResetAutomata();

	//input a character for the automata to process
	eOutput ProcessChar(char nextChar);

	//ask the automaton about its current state
	eOutput CurrentState();
	

private:
	int mState;
	eOutput mOutput;

	tStateMap mStateMap;
	tTransitionMap mTransitionMap;
	std::set<int> mAcceptStates;
	std::map<char, int>::iterator mTempIt;
};
