#include "..\include\Automaton.h"


Automaton::Automaton(tStateMap states, tTransitionMap transitions, std::set<int> acceptStates):
	mState(0),
	mOutput(MAYBE),
	mStateMap(states),
	mTransitionMap(transitions),
	mAcceptStates(acceptStates)
{
}


Automaton::~Automaton(void)
{
}


void Automaton::ResetAutomata()
{
	mState = 0;
	mOutput = MAYBE;
}

Automaton::eOutput Automaton::ProcessChar(char nextChar)
{
	//if we were in an error state, exit early
	if(mOutput == NO || mOutput == NO_BUT_WAS)
	{
		return NO;
	}

	//check if this next character exists in the state map
	if(mStateMap[mState].count(nextChar))
	{
		//sweet, no error. Check where we should go next
		//does a transition exist?
		if((mTempIt = mTransitionMap[mState].find(nextChar)) != mTransitionMap[mState].end())
		{
			//transition exists, sweet follow it
			mState = mTempIt->second;
			//is this now an accept state?
			if(mAcceptStates.count(mState))
			{
				//if so we want to say yes
				mOutput = YES;
			}
			else
			{
				mOutput = MAYBE;
				//otherwise, change output to maybe
			}
		}
		else
		{
			//no transition exists, so we just want to keep our same state and output
			//...so do nothing
		}
	}
	else
	{
		//the character was not in the state map for that state
		mState = -1;
		if(mOutput == YES)
			mOutput = NO_BUT_WAS;
		else
			mOutput = NO;
	}

	return mOutput;
}

Automaton::eOutput Automaton::CurrentState()
{
	return mOutput;
}
