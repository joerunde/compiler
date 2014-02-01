#include "..\include\Scanner.h"
#include "..\include\Tokens.h"
#include <iostream>

Scanner::Scanner(void):
	mBinopToken(new BinopToken("")),
	mBoolToken(new BoolToken("")),
	mBracketToken(new BracketToken("")),
	mFloatToken(new FloatToken("")),
	mIDToken(new IDToken("")),
	mIntToken(new IntegerToken("")),
	mStrToken(new StrToken("")),
	mUnopToken(new UnopToken(""))
{
	mBinopToken->SetupAutomata();
	mBoolToken->SetupAutomata();
	mBracketToken->SetupAutomata();
	mFloatToken->SetupAutomata();
	mIDToken->SetupAutomata();
	mIntToken->SetupAutomata();
	mStrToken->SetupAutomata();
	mUnopToken->SetupAutomata();
	ResetStacks();
}

Scanner::~Scanner(void)
{
}

std::vector<Token*> Scanner::ScanFile(std::string filename)
{
	mTokenPile.clear();
	Token* temp;

	mFile.open(filename.c_str());
	if(!mFile.is_open())
	{
		std::cout << "Error: No file\n";
		return mTokenPile;
	}

	while(!mFile.eof())
	{
		mChar = mFile.peek();

		if(mChar == -1)
		{
			if(mCurrentLexeme.size() == 0)
				break;
			//eof hit, handle it by hand right now
			temp = GetFirstAccepted();
			if(!temp)
			{
				//no finished token was found, error
				std::cout << "Err: \"" << mCurrentLexeme << "\"" << std::endl;
				ResetStacks();
				break;
			}
			else
			{
				//we had a complete token, add it and move on
				PushToken(temp);
				break;
			}
		}

		if(mChar == ' ' && mCurrentLexeme.size() == 0)
		{
			//if this is a space and nothing was lexing, throw it away
			mFile.get();
			std::cout << " ";
			continue;
		}

		if(mChar == '\n')
		{
			//we hit an eol char, we don't want to process this
			//instead we'll cut off token processing here and add what we have
			//but first, definitely consume it
			mFile.get();

			if(mCurrentLexeme.length() == 0)
			{
				//we had nothing, that's totally okay
				std::cout << std::endl;
				continue;
			}
			else
			{
				temp = GetFirstAccepted();
				if(!temp)
				{
					//no finished token was found, error
					std::cout << "Err: \"" << mCurrentLexeme << "\"" << std::endl;
					ResetStacks();
					continue;
				}
				else
				{
					//we had a complete token, add it and move on
					PushToken(temp);
					std::cout << std::endl;
					continue;
				}
			}
		}
		else
		{
			//not an eol char, so let's process it
			if(ProcessChar(mChar))
			{
				//there's still automata matching, consume and move on
				mFile.get();
			}
			else
			{
				//the last automata failed, backtrace 1 character and see if we
				//had anything good
				temp = GetLastGoodRejected();
				if(!temp)
				{
					//uh oh, nothing ever matched, error
					std::cout << "Err: \"" << mCurrentLexeme << mChar << "\"" << std::endl;
					//if there was nothing being lexed, consume the character, it's a dud
					if(mCurrentLexeme.size() == 0)
					{
						mFile.get();
					}
					ResetStacks();
					continue;
				}
				else
				{
					//we have a matched token, send it to the pile
					PushToken(temp);
					continue;
				}
			}
		}

		mCurrentLexeme.append(1, mChar);
	}

	//reset ALL the things, except the token pile ;)
	ResetStacks();
	//close file
	mFile.close();
	return mTokenPile;
}

Token* Scanner::GetLastGoodRejected()
{
	for(int c = mRejectedStack.size() - 1; c >= 0; c--)
	{
		//just make sure that this was accepted last character
		if(mRejectedStack[c]->GetAutomaton()->CurrentState() == Automaton::NO_BUT_WAS)
			return mRejectedStack[c];
	}
	//null my bor =(
	return 0;
}

Token* Scanner::GetFirstAccepted()
{
	for(unsigned int c = 0; c < mAutomataStack.size(); c++)
	{
		if(mAutomataStack[c]->GetAutomaton()->CurrentState() == Automaton::YES)
			return mAutomataStack[c];
	}
	//null my bor =(
	return 0;
}

bool Scanner::ProcessChar(char nextChar)
{
	//clear out old rejected automata
	mRejectedStack.clear();
	Automaton::eOutput state;

	for(int c = (int)mAutomataStack.size() - 1; c >= 0; c--)
	{
		mAutomataStack[c]->GetAutomaton()->ProcessChar(nextChar);
		state = mAutomataStack[c]->GetAutomaton()->CurrentState();
		if(state == Automaton::NO)
		{
			//straight up error, delete it
			mAutomataStack.erase(mAutomataStack.begin() + c);
		}
		if(state == Automaton::NO_BUT_WAS)
		{
			//was in an accept state, but then errored. Keep it around for an interation
			mRejectedStack.push_back(mAutomataStack[c]);
			mAutomataStack.erase(mAutomataStack.begin() + c);
		}
	}
	//return whether any automata are left
	return(mAutomataStack.size() != 0);
}

void Scanner::ResetStacks()
{
	mCurrentLexeme.clear();

	mBinopToken->GetAutomaton()->ResetAutomata();
	mBoolToken->GetAutomaton()->ResetAutomata();
	mBracketToken->GetAutomaton()->ResetAutomata();
	mFloatToken->GetAutomaton()->ResetAutomata();
	mIDToken->GetAutomaton()->ResetAutomata();
	mIntToken->GetAutomaton()->ResetAutomata();
	mStrToken->GetAutomaton()->ResetAutomata();
	mUnopToken->GetAutomaton()->ResetAutomata();

	mAutomataStack.clear();
	mAutomataStack.push_back(mIntToken);
	mAutomataStack.push_back(mFloatToken);
	mAutomataStack.push_back(mUnopToken);
	mAutomataStack.push_back(mBinopToken);
	mAutomataStack.push_back(mBoolToken);
	mAutomataStack.push_back(mBracketToken);
	mAutomataStack.push_back(mStrToken);
	mAutomataStack.push_back(mIDToken);
	mRejectedStack.clear();
}

void Scanner::PushToken(Token* token)
{
	//mCurrentLexeme.append(1, mChar);
	Token* temp = token->GetToken(mCurrentLexeme);
	mTokenPile.push_back(temp);
	std::cout << "<" << temp->GetType() << ", '" << temp->GetLexeme() << "'>";
	ResetStacks();
}