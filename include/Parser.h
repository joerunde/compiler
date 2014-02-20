#pragma once
#include <string>

class SymbolTable;
class Scanner;
class Token;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	void SetScanner(Scanner* scanner);
	void SetSymbolTable(SymbolTable* table);

	void Parse();

private:
	//point to a scanner and a symbol table
	SymbolTable* mTable;
	Scanner* mScanner;

	std::string mIndent;

	void error(std::string msg);

	void printmsg(std::string msg);
	void print(Token* token);

	bool isRB(Token* token);
	bool isLB(Token* token);
	bool isConstant(Token* token);
	bool isInt(Token* token);
	bool isID(Token* token);
	bool isReal(Token* token);
	bool isBool(Token* token);
	bool isStr(Token* token);
	bool isAssign(Token* token);
	bool isUnop(Token* token);
	bool isBinop(Token* token);
	
	bool isTyp(Token* token);
	bool isKeyword(Token* token);
	bool isWhile(Token* token);
	bool isLet(Token* token);
	bool isIf(Token* token);
	bool isStdout(Token* token);


	/* implicit stack parsing functions */

	void T();
	void S();
	void Sp();
	void Spp();
	void E();
	void O();
	void Op();
	void St();
	void Stp();
	void Stpp();
	void EL();
	void ELp();
	void VL();
	void VLp();

};

