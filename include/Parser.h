#pragma once
#include <string>
#include <vector>

class SymbolTable;
class Scanner;
class Token;

class Node
{
public:
	Node(Node* parent, Token* term)
	{mParent = parent; mTerm = term;}
	Node(Node* parent, std::string nonterm)
	{mParent = parent; mNonterm = nonterm;}

	Node* addChild(Token* term)
	{
		Node* tmp = new Node(this, term);
		mKids.push_back(tmp);
		return tmp;
	}
	Node* addChild(std::string nonterm)
	{
		Node* tmp = new Node(this, nonterm);
		mKids.push_back(tmp);
		return tmp;
	}

	std::vector<Node*> getKids(){return mKids;}
	Node* getParent(){return mParent;}
private:
	std::string mNonterm;
	Token* mTerm;
	std::vector<Node*> mKids;
	Node* mParent;
};



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

