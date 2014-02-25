#pragma once
#include <string>
#include <vector>

class SymbolTable;
class Scanner;
class Token;
class Node;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	void SetScanner(Scanner* scanner);
	void SetSymbolTable(SymbolTable* table);

	Node* Parse();

private:
	//point to a scanner and a symbol table
	SymbolTable* mTable;
	Scanner* mScanner;

	std::string mIndent;

	void error(std::string msg);

	void printmsg(std::string msg);
	void print(Token* token);

	/* implicit stack parsing functions */

	void T(Node* node);
	void S(Node* node);
	void Sp(Node* node);
	void Spp(Node* node);
	void E(Node* node);
	void O(Node* node);
	void Op(Node* node);
	void St(Node* node);
	void Stp(Node* node);
	void Stpp(Node* node);
	void EL(Node* node);
	void ELp(Node* node);
	void VL(Node* node);
	void VLp(Node* node);

};

