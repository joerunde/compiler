#pragma once

#include <set>
#include <map>
#include <string.h>
#include "Token.h"

/* 
	Class defining a deterministic finite automaton, to be used with a lexical analyzer.
	Accept state for the Automaton are tied to types of tokens that will be created with the accepted
	lexeme.
	Accept states support 1 or 2 character push back.
*/

//a state is defined as a unique integer id with a set of characters that are valid to read next
typedef std::map<int, std::set<char> > tStateMap;
//a transition map defines, for each state, a mapping of new states to transition to upon seeing a character
typedef std::map<int, std::map<char, int> > tTransitionMap;
//if a character read is not defined by the state, instead of erroring an else map can point to a new
//state to transition to. This is just for ease of defining the automata in a couple places
typedef std::map<int, int> tElseMap;

class Automaton
{
public:
	//By convention, 0 is the starting state. After that put in any positive int for the state numbers.
	//If a character exists for a state in the state map, but does NOT exists in the transition map
	//for that state, it is assumed that a transition exists that loops back to the same state.
	Automaton();
	~Automaton();

	enum eOutput{
		YES,		//Currently in an accept state, please grab a token
		NO,			//Currently in an error state, throw out all characters and reset
		YES_PUSH_1, //In an accept state, but push 1 character back to the stream before taking a token
		YES_PUSH_2, //In an accept state, but push 2 characters back to the stream before taking a token
		MAYBE,		//Not in an accept or error state, still traversing
	};

	//reset internal state to the starting state
	void ResetAutomata();

	//input a character for the automata to process
	eOutput ProcessChar(char nextChar);

	//ask the automaton about its current state
	eOutput CurrentState();

	//grab the last created token
	Token* GetToken();

	//grab the last errored lexeme
	std::string GetError();
	
	bool HasStarted();

protected:

	void CheckAcceptState();

	int mState;
	eOutput mOutput;

	Token* mOutputToken;

	tStateMap mStateMap;
	tTransitionMap mTransitionMap;
	tElseMap mElseMap;
	std::set<int> mAcceptStatesNoPush; //accept states with no push back
	std::set<int> mAcceptPushOneStates; //accept states with 1 push back
	std::set<int> mAcceptPushTwoStates; //accept states with 2 push back
	std::map<char, int>::iterator mTempIt;

	std::map<int, Token*> mAcceptTokens;

	std::string mLexeme;
	std::string mFailedLexeme;
};
