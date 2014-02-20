#include "../include/Automaton.h"


Automaton::Automaton():
	mState(0)
{
}


Automaton::~Automaton(void)
{
}


void Automaton::ResetAutomata()
{
	mLexeme.clear();
	mState = 0;
	mOutput = MAYBE;
}

Automaton::eOutput Automaton::ProcessChar(char nextChar)
{
	//if we were in an error state, exit early
	if(mOutput == NO)
	{
		return NO;
	}

	//check if this next character exists in the state map
	if(mStateMap[mState].count(nextChar))
	{
		//sweet, no error. Add this character to the lexeme
		mLexeme.append(1, nextChar);
		//Check where we should go next
		//does a transition exist?
		if((mTempIt = mTransitionMap[mState].find(nextChar)) != mTransitionMap[mState].end())
		{
			//transition exists, sweet follow it
			mState = mTempIt->second;
			CheckAcceptState();
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
		//check if there's an else state
		if(mElseMap.count(mState))
		{
			//yeah there is, so go there, set output, and add character
			mState = mElseMap[mState];
			mLexeme.append(1, nextChar);
			CheckAcceptState();	
		}
		else
		{
			//well we errored
			mOutput = NO;
			mState = -1;
			mFailedLexeme = mLexeme;
		}
	}

	return mOutput;
}

void Automaton::CheckAcceptState()
{
	//is this now an accept state? 
	if(mAcceptStatesNoPush.count(mState))
	{
		//if so we want to say yes
		mOutput = YES;
		mOutputToken = mAcceptTokens[mState]->GetToken(mLexeme);
	}
	else if(mAcceptPushOneStates.count(mState))
	{
		//or yes but push 1 back
		mOutput = YES_PUSH_1;
		mLexeme.erase(mLexeme.end() - 1, mLexeme.end());
		mOutputToken = mAcceptTokens[mState]->GetToken(mLexeme);
	}
	else if(mAcceptPushTwoStates.count(mState))
	{
		//or yes but push two back
		mOutput = YES_PUSH_2;
		mLexeme.erase(mLexeme.end() - 2, mLexeme.end());
		mOutputToken = mAcceptTokens[mState]->GetToken(mLexeme);
	}
	else
	{
		//otherwise, change output to maybe
		mOutput = MAYBE;	
	}
}

Automaton::eOutput Automaton::CurrentState()
{
	return mOutput;
}

bool Automaton::HasStarted()
{
	return(mState != 0);
}

Token* Automaton::GetToken()
{
	return mOutputToken;
}

std::string Automaton::GetError()
{
	return mFailedLexeme;
}