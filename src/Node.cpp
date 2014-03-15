#include "../include/Node.h"
#include "../include/Token.h"
#include "../include/Parser.h"
#include "../include/IDToken.h"
#include <iostream>

Node::Node():
	mitof(false),
	mftoi(false),
	mType(TYPE_NONE),
	mTerm(0)
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
		mKids.insert(mKids.begin(), new Node(this, new BlankToken(": main")));
		mKids[1]->recursiveProcess();
		mKids.push_back(new Node(this, new BlankToken("; main"))); 
	}
	quickPost();
}

void Node::declareID(eVarType type)
{
	if(mTerm->isID())
	{
		//reinterpret cast
		//hell yeah we just went there
		IDToken* temp = reinterpret_cast<IDToken*>(mTerm);
		temp->setType(type);
	}
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
			if(mTerm->isID())
			{
				mType = (eVarType)mTerm->GetReturnType(0);
				if(mType == TYPE_NONE)
					std::cout << "ERROR, UNDECLARED IDENTIFIER\n";
				return mType;
			}
			if(mTerm->isTyp())
			{
				//it's late, we're grabbing type from strings here
				std::string typestr = mTerm->GetLexeme();
				if(typestr == "float")
					return TYPE_FLOAT;
				if(typestr == "int")
					return TYPE_INT;
				if(typestr == "bool")
					return TYPE_BOOL;
				if(typestr == "string")
					return TYPE_STRING;
			}
		}
		//default int
		return TYPE_INT;
	}

	//check if this is an operator which needs to deal with floats vs. ints
	//or if this an if/while
	if(mTerm != 0)
	{
		if(mTerm->isBinop() && !mTerm->isAssign())
		{
			//assume two children, because binop
			eVarType x1, x2;
			x1 = mKids[0]->recursiveProcess();
			x2 = mKids[1]->recursiveProcess();

			mType = checkType(x1, x2);
			return Node::eVarType(mTerm->GetReturnType(mType));
		}//always return before here, because kids have already been processed

		if(mTerm->isAssign())
		{
			eVarType lhs, rhs;
			//right side first because we aint a part of the system
			rhs = mKids[1]->recursiveProcess();
			lhs = mKids[0]->recursiveProcess();
			if(lhs != rhs)
			{
				if(lhs == TYPE_FLOAT && rhs == TYPE_INT)
				{
					mKids[1] = mKids[1]->addParentConversion(true);
				}
				else if(lhs == TYPE_INT && rhs == TYPE_FLOAT)
				{
					mKids[1] = mKids[1]->addParentConversion(false);
				}
				else
				{
					std::cout << "Type error, cannot assign ";
					printType(rhs);
					std::cout << " to ";
					printType(lhs);
					std::cout << std::endl;
				}
			}
			mType = lhs;
			return mType;
		}//kids processed before here

		if(mTerm->isIf())
		{
			bool hasElse = false;
			if(mKids.size() == 3)
			{
				hasElse = true;
			}
			//tack on the endif
			mKids.push_back(new Node(this, new BlankToken("endif")));
			//put the else in if necessary
			if(hasElse)
				mKids.insert(mKids.begin() + 2, new Node(this, new BlankToken("else")));
			//put in the node for the if print
			mKids.insert(mKids.begin() + 1, new Node(this, mTerm));
			//then delort the term
			mTerm = 0;
		}
		else if(mTerm->isWhile())
		{
			//add the begin
			mKids.insert(mKids.begin(), new Node(this, new BlankToken("begin")));
			//and the end of the loop
			mKids.push_back(new Node(this, new BlankToken("repeat")));
			//put in the node for the while print
			mKids.insert(mKids.begin() + 2, new Node(this, mTerm));
			//then delort this term
			mTerm = 0;
		}
		else if(mTerm->isLet())
		{
			//slap this up in the beginning of T's kids
			Node* tmp = this;
			while(tmp->mNonterm != "T")
			{
				tmp = tmp->mParent;
			}
			tmp->mKids.insert(tmp->mKids.begin(), this);
			Node* T = tmp;
			//delort this from parent's kids (by adding empty node)
			tmp = this->mParent;
			this->mParent = T;
			for(int c = 0; c < tmp->mKids.size(); c++)
			{
				if(tmp->mKids[c] == this)
					tmp->mKids[c] = new Node();
			}
		}
	}

	if(mNonterm == "VL")
	{
		//here we're declaring a variable
		//grab type from type token, should be a leaf
		eVarType declare = mKids[1]->recursiveProcess();
		//declare the variable, so that we know it's type later
		mKids[0]->declareID(declare);
		//add a new child node at the beginning to do the actual gforth declare
		//abusing blank tokens because sure
		BlankToken* variable;
		switch(declare)
		{
		case TYPE_INT:
		case TYPE_BOOL:
			variable = new BlankToken("variable");
			break;
		case TYPE_FLOAT:
			variable = new BlankToken("fvariable");
			break;
		case TYPE_STRING:
			variable = new BlankToken("2variable");
			break;
		default:
			variable = new BlankToken();
			break;
		}
		mKids.erase(mKids.begin() + 1);//erase the type node, don't want to print it
		mKids.insert(mKids.begin(), new Node(this, variable));//put in the gforth declare node
		mKids[2]->recursiveProcess();
		return TYPE_NONE;//no type for declarations
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
	if((left == TYPE_FLOAT && right == TYPE_INT) || (left == TYPE_INT && right == TYPE_FLOAT))
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

void Node::quickPost(bool noRef)
{
	bool kidsDone = false;
	//edge case for assigning, need to flip around kids and send special flag
	if(mTerm != 0)
	{
		if(mTerm->isAssign())
		{
			mKids[1]->quickPost();
			mKids[0]->quickPost(true);
			kidsDone = true;
		}
	}
	//also edge case for declaring, need special flag as well
	if(mNonterm == "VL")
	{
		mKids[0]->quickPost();
		mKids[1]->quickPost(true);
		mKids[2]->quickPost();
		kidsDone = true;
	}

	if(!kidsDone)
	{
		for(int c = 0; c < mKids.size(); c++)
		{
			mKids[c]->quickPost();
		}
	}

	if(mTerm != 0)
	{
		if(noRef == true)
		{
			std::cout << mTerm->GetLexeme() << " ";
		}
		else
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

Node* Node::insertFrontChild(Token* term)
{
	Node* tmp = new Node(this, term);
	mKids.insert(mKids.begin(), tmp);
	return tmp;
}

std::vector<Node*> Node::getKids(){
	return mKids;
}

Node* Node::getParent()
{
	return mParent;
}
