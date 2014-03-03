#include "../include/Node.h"
#include "../include/Token.h"
#include "../include/Parser.h"
#include <iostream>

Node::Node():
	mitof(false),
	mftoi(false),
	mType(TYPE_NONE)
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

Node::eVarType Node::recursiveProcess()
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
					mType = TYPE_FLOAT;
					return mType;
				}
				if(mTerm->isStr())
				{
					mType = TYPE_STRING;
					return mType;
				}
				if(mTerm->isBool())
				{
					mType = TYPE_BOOL;
					return mType;
				}
			}
		}
		//default int
		return TYPE_INT;
	}

	//check if this is an operator which needs to deal with floats vs. ints
	if(mTerm != 0)
	{
		if(mTerm->isBinop())
		{
			//assume two children, because binop
			eVarType x1, x2;
			x1 = mKids[0]->recursiveProcess();
			x2 = mKids[1]->recursiveProcess();

			mType = checkType(x1, x2);
			return Node::eVarType(mTerm->GetReturnType(mType));
		}//always return before here, because kids have already been processed
	}

	//pass through if 1 kid, b/c this is unop or nonproduction
	if(mKids.size() == 1)
	{
		mType = mKids[0]->recursiveProcess();
		return mType;
	}

	//anything else is a multi expression branch, right.........?
	//so return no type
	for(int c = 0; c < mKids.size(); c++)
	{
		mKids[c]->recursiveProcess();
	}
	return TYPE_NONE;
}

Node::eVarType Node::checkType(eVarType left, eVarType right)
{
	//if there's no conflict, just return
	if(left == right)
		return left;
	//there is a conflict, is it float vs. int?
	if(left == TYPE_FLOAT || right == TYPE_FLOAT)
	{
		//if so, we can take care of it, and convert this op to float
		if(left == TYPE_INT)
		{
			mKids[0] = mKids[0]->addParentConversion(true);
		}
		if(right == TYPE_INT)
		{
			mKids[1] = mKids[1]->addParentConversion(true);
		}
		return TYPE_FLOAT;
	}
	//otherwise, we can't take care of it
	std::cout << "Type error, cannot operate on ";
	printType(left);
	std::cout << " and ";
	printType(right);
	std::cout << std::endl;
	return TYPE_NONE;
}

void Node::printType(Node::eVarType type)
{
	switch(type)
	{
	case TYPE_INT:
		std::cout << "INT";
		break;
	case TYPE_FLOAT:
		std::cout << "FLOAT";
		break;
	case TYPE_STRING:
		std::cout << "STRING";
		break;
	case TYPE_BOOL:
		std::cout << "BOOL";
		break;
	case TYPE_NONE:
		std::cout << "NO TYPE";
		break;
	}
}

void Node::quickPost()
{
	for(int c = 0; c < mKids.size(); c++)
	{
		mKids[c]->quickPost();
	}
	if(mTerm != 0)
	{
		std::cout << mTerm->GetLexeme(mType) << " ";
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
	if(itof)
		tmp->mType = TYPE_FLOAT;
	else
		tmp->mType = TYPE_INT;
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
