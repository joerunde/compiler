#include "../include/Node.h"
#include "../include/Token.h"
#include "../include/Parser.h"
#include <iostream>

Node::Node():
	mitof(false),
	mftoi(false),
	mIsFloat(false)
{}

Node::Node(Node* parent, Token* term)
{
	mParent = parent; 
	mTerm = term;
	mNonterm = "";
	init();
}

Node::Node(Node* parent, std::string nonterm)
{
	mParent = parent; 
	mNonterm = nonterm;
	mTerm = 0;
	init();
}

void Node::processTree()
{
	if(mKids.size() > 0)
	{
		mKids[0]->recursiveProcess();
	}

	quickPost();
}

bool Node::recursiveProcess()
{
	//check if this is a leaf
	if(mKids.size() == 0)
	{
		if(mTerm != 0)
		{
			if(mTerm->isConstant())
			{
				if(mTerm->isReal())
				{
					//need fp stack
					mIsFloat = true;
					return true;
				}
			}
		}
		//dont need fp stack
		mIsFloat = false;
		return false;
	}

	//check if this is an operator which needs to deal with floats vs. ints
	if(mTerm != 0)
	{
		if(mTerm->isBinop())
		{
			//assume two children, because binop
			bool x1, x2;
			x1 = mKids[0]->recursiveProcess();
			x2 = mKids[1]->recursiveProcess();
			//check if either needs float
			if(x1 || x2)
			{
				if(!x1)
				{
					mKids[0] = mKids[0]->addParentConversion(true);
				}
				if(!x2)
				{
					mKids[1] = mKids[1]->addParentConversion(true);
				}
				mIsFloat = true;
			}
			else
				mIsFloat = false;
			return mIsFloat;
		}//always return before here, because kids have already been processed
	}

	//pass through if 1 kid, b/c this is unop or nonproduction
	if(mKids.size() == 1)
	{
		return mKids[0]->recursiveProcess();
	}

	//anything else is a multi expression branch, right.........?
	//so return false? (int stack by default)
	for(int c = 0; c < mKids.size(); c++)
	{
		mKids[c]->recursiveProcess();
	}
	return false;
}

void Node::quickPost()
{
	for(int c = 0; c < mKids.size(); c++)
	{
		mKids[c]->quickPost();
	}
	if(mTerm != 0)
	{
		std::cout << mTerm->GetLexeme() << " ";
	}
	if(mitof)
	{
		std::cout << "s>f ";
	}
	if(mftoi)
	{
		std::cout << "f>s ";
	}
}

Node* Node::addParentConversion(bool itof)
{
	Node* tmp = new Node(mParent, "");
	mParent = tmp;
	tmp->mKids.push_back(this);
	tmp->mitof = itof;
	tmp->mftoi = !itof;
	return tmp;
}

Node* Node::addChild(Token* term)
{
	Node* tmp = new Node(this, term);
	mKids.push_back(tmp);
	return tmp;
}

Node* Node::addChild(std::string nonterm)
{
	Node* tmp = new Node(this, nonterm);
	mKids.push_back(tmp);
	return tmp;
}

std::vector<Node*> Node::getKids(){
	return mKids;
}

Node* Node::getParent()
{
	return mParent;
}
