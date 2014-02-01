#pragma once
#include <string>
#include <fstream>
#include "Token.h"
#include <vector>

class Scanner
{
public:
	Scanner(void);
	~Scanner(void);

	std::vector<Token*> ScanFile(std::string filename);

private:
	std::ifstream mFile;

	std::vector<Token*> mTokenPile;

	std::vector<Token*> mAutomataStack;
	std::vector<Token*> mRejectedStack;

	std::string mCurrentLexeme;

	char mChar;

	Token* GetLastGoodRejected();
	Token* GetFirstAccepted();
	bool ProcessChar(char c);
	void ResetStacks();
	void PushToken(Token* token);

	/* Tokens! */
	Token* mBinopToken;
	Token* mBoolToken;
	Token* mBracketToken;
	Token* mFloatToken;
	Token* mIDToken;
	Token* mIntToken;
	Token* mStrToken;
	Token* mUnopToken;

};

