#pragma once

#include <string>
#include <vector>
class Token;

class Node
{
public:
	Node(void);
	Node(Node* parent, Token* term);
	Node(Node* parent, std::string nonterm);

	Node* addChild(Token* term);
	Node* addChild(std::string nonterm);

	std::vector<Node*> getKids();
	Node* getParent();

	void processTree();

	bool hasToken();

private:
	std::string mNonterm;
	Token* mTerm;
	std::vector<Node*> mKids;
	Node* mParent;

	void quickPost();

	//returns whether the node is on the float stack
	bool recursiveProcess(); 
	
	Node* addParentConversion(bool itof);

	//are we on the floating point stack? If not then int stack
	bool mIsFloat;

	//is this an int to float conversion node?
	bool mitof;

	//is this a float to int conversion node?
	bool mftoi;

	void init(){mitof = false; mftoi = false; mIsFloat = false;}
};

