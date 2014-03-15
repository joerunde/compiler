#pragma once

#include <string>
#include <vector>
#include <map>
#include <string>
class Token;

class Node
{
public:
	Node(void);
	Node(Node* parent, Token* term);
	Node(Node* parent, std::string nonterm);

	Node* addChild(Token* term);
	Node* addChild(std::string nonterm);
	Node* insertFrontChild(Token* term);

	std::vector<Node*> getKids();
	Node* getParent();

	void processTree();

	bool hasToken();

	enum eVarType{
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_NONE
	};

private:
	std::string mNonterm;
	Token* mTerm;
	std::vector<Node*> mKids;
	Node* mParent;
	
	void quickPost(bool noRef = false);

	//sets and returns the type of the branch at this node
	//adds conversion nodes where necessary
	eVarType recursiveProcess();

	//declare an identifier
	void declareID(eVarType type);

	//type check for a binary operator
	eVarType checkType(eVarType left, eVarType right);
	
	Node* addParentConversion(bool itof);

	void printType(eVarType type);
	
	//What variable type is this branch of the parse tree dealing with?
	eVarType mType;

	//is this an int to float conversion node?
	bool mitof;

	//is this a float to int conversion node?
	bool mftoi;

	void init(){mitof = false; mftoi = false; mType = TYPE_NONE;}
};

