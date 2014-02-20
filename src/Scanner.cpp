#include "../include/Scanner.h"
#include "../include/Tokens.h"
#include "../include/Automaton.h"
#include "../include/IBTLAutomaton.h"
#include <iostream>

Scanner::Scanner(void)
{
	mDFA = new IBTLAutomaton();
}

Scanner::~Scanner(void)
{
}

void Scanner::setTable(SymbolTable* table)
{
	Token::setSymbolTable(table);
}

bool Scanner::OpenFile(std::string filename)
{
	mFile.open(filename.c_str());
	if(!mFile.is_open())
	{
		std::cout << "Error: No file\n";
		return false;
	}

	mToken1 = ScanToken();
	mToken2 = ScanToken();

	return true;
}

void Scanner::CloseFile()
{
	mFile.close();
}

Token* Scanner::GetNextToken()
{
	Token* temp = mToken1;
	mToken1 = mToken2;
	mToken2 = ScanToken();
	return temp;
}

Token* Scanner::PeekOneToken()
{
	return mToken1;
}

Token* Scanner::PeekTwoTokens()
{
	return mToken2;
}

Token* Scanner::ScanToken()
{
	Token* temp = 0;
	mDFA->ResetAutomata();

	while(!mFile.eof())
	{
		mChar = mFile.peek();

		if((mChar == ' ' || mChar == 9 || mChar == '\n') && !mDFA->HasStarted())
		{
			//if this is a space and nothing was lexing, throw it away
			mFile.get();
			std::cout << mChar;
			continue;
		}	
		else
		{
			//not whitespace, process it
			Automaton::eOutput state = mDFA->ProcessChar(mChar);
			if(state == Automaton::MAYBE)
			{
				//automaton is still matching, consume
				mFile.get();
			}
			else if(state == Automaton::NO)
			{
				//error :(  print, reset, consume and move on
				std::string err = mDFA->GetError();
				if(err.size() == 0 && mChar == -1)
				{
					//if it was only the eof char, meh just break
					break;
				}
				std::cout << "Err: \"" << err << mChar << "\"" << std::endl; 
				mDFA->ResetAutomata();
				mFile.get();
			}
			else
			{
				//something accepted! yay!
				//figure out what to do with characters and things
				if(state == Automaton::YES)
				{
					//no push back, so consume
					mFile.get();
				}
				else if(state == Automaton::YES_PUSH_1)
				{
					//1 push back, so just dont consume
				}
				else if(state == Automaton::YES_PUSH_2)
				{
					//2 push backs, so we need to push back one
					std::streamoff pos = mFile.tellg();
					mFile.seekg(pos - 1);
				}


				temp = mDFA->GetToken();
				
				//break to return the token
				break;
				
			}
		}
	}

	return temp;
}
