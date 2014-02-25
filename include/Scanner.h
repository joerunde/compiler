#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Automaton.h"

class SymbolTable;
class Token;

class Scanner
{
public:
	Scanner(void);
	~Scanner(void);

	bool OpenFile(std::string filename);
	Token* GetNextToken();
	Token* PeekOneToken();
	Token* PeekTwoTokens();
	void CloseFile();

	void setTable(SymbolTable* table);

private:
	std::ifstream mFile;

	Token* ScanToken();

	Automaton* mDFA;

	char mChar;

	Token* mBlank;

	Token* mToken1;
	Token* mToken2;

	Token* GetToken();
	bool ProcessChar(char c);
	void ResetStack();
};

