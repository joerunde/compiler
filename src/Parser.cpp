#include "../include/Parser.h"
#include "../include/SymbolTable.h"
#include "../include/Tokens.h"
#include "../include/Scanner.h"
#include "../include/Node.h"
#include <iostream>
#include <typeinfo>

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

void Parser::SetScanner(Scanner* scanner)
{
	mScanner = scanner;
}

void Parser::SetSymbolTable(SymbolTable* table)
{
	mTable = table;
}

void Parser::printmsg(std::string msg)
{
	std::cout << mIndent << msg << "\n";
}

Node* Parser::Parse()
{
	Node* parsetree = new Node(0, "T");
	mIndent.clear();
	try{
		T(parsetree);
	}catch(...)
	{
		std::cout << "\nparser barfed\n\n";
		//nothing, just quit
	}
	parsetree->processTree();
	return parsetree;
}

void Parser::T(Node* node)
{
	std::cout << "\n";
	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isLB())
	{
		printmsg("T->[S]");
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		S(node->addChild("S"));
		tmp = mScanner->PeekOneToken();
		if(!tmp->isRB())
		{
			error("Error in T production\n");
		}
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}
}

void Parser::S(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	Token* tmp2 = mScanner->PeekTwoTokens();
	if( tmp->isLB() && (tmp2->isLB() || tmp2->isRB() || tmp2->isConstant() || tmp2->isID() ) )
	{
		printmsg("S->[S'S''");
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		Sp(node->addChild("S'"));
		Spp(node->addChild("S''"));
	}
	else
	{
		printmsg("S->ES''");
		E(node->addChild("E"));
		Spp(node->addChild("S''"));
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Sp(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isRB())
	{
		printmsg("S'->]");
		node->addChild(tmp);
		//print(tmp);
		mScanner->GetNextToken();
	}
	else
	{
		printmsg("S'->S]");
		S(node->addChild("S"));
		tmp = mScanner->PeekOneToken();
		if(!tmp->isRB())
		{
			error("Error in S' production\n");
		}
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}

	mIndent.erase(mIndent.end() - 1, mIndent.end());
}

void Parser::Spp(Node* node)
{
	Token* tmp = mScanner->PeekOneToken();
	if(!tmp->isRB())
	{
		printmsg("S''->SS''");
		S(node->addChild("S"));
		Spp(node->addChild("S''"));
	}
	else
		printmsg("S''->empty");
}

void Parser::E(Node* node)
{
	//mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	Token* tmp2 = mScanner->PeekTwoTokens();
	if(tmp->isConstant() || tmp->isID())
	{
		printmsg("E->O");
		O(node->addChild("O"));
	}
	else if(tmp->isLB() && ( tmp2->isUnop() || tmp2->isBinop() ))
	{
		printmsg("E->O");
		O(node->addChild("O"));
	}
	else
	{
		printmsg("E->St");
		St(node->addChild("St"));
	}

	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::O(Node* node)
{
	mIndent.append("\t");
	
	Token* tmp = mScanner->PeekOneToken();

	if(tmp->isConstant() || tmp->isID())
	{
		printmsg("O->ID|constant");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}
	else if(tmp->isLB())
	{
		printmsg("O->[O'");
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		Op(node->addChild("O'"));
	}
	else
	{
		error("Error in O production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Op(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isAssign())
	{
		printmsg("O'->:= ID O]");
		//branch here on operator
		node = node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		tmp = mScanner->PeekOneToken();
		if(!tmp->isID())
		{
			error("Error in O' production\n");
		}
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
	}
	else if(tmp->isUnop())
	{
		printmsg("O'->Unop O]");
		//branch on operator
		node = node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
	}
	else if(tmp->isBinop())
	{
		printmsg("O'->Binop O O]");
		//branch on operator
		node = node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
		O(node->addChild("O"));
	}

	//common to all productions
	tmp = mScanner->PeekOneToken();
	if(!tmp->isRB())
	{
		error("Error in O' production\n");
	}
	//node->addChild(tmp);
	print(tmp);
	mScanner->GetNextToken();

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::St(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isLB())
	{
		printmsg("St->[St'");
		//node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		Stp(node->addChild("St'"));
	}
	else
	{
		error("Error in St production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Stp(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isKeyword())
	{
		mScanner->GetNextToken();
		if(tmp->isWhile())
		{
			printmsg("St'->while E EL ]");
			//branch on operator
			node = node->addChild(tmp);
			print(tmp);
			E(node->addChild("E"));
			EL(node->addChild("EL"));
			tmp = mScanner->GetNextToken();
			if(!tmp->isRB())
			{
				error("Error in St' production\n");
			}
			//node->addChild(tmp);
			print(tmp);
		}
		else if(tmp->isIf())
		{
			printmsg("St'->if E E St''");
			//branch on operator
			node = node->addChild(tmp);
			print(tmp);
			E(node->addChild("E"));
			E(node->addChild("E"));
			Stpp(node->addChild("Stpp"));
		}
		else if(tmp->isLet())
		{
			printmsg("St'->let [VL] ]");
			//branch on operator
			node = node->addChild(tmp);
			print(tmp);
			tmp = mScanner->PeekOneToken();
			if(!tmp->isLB())
			{
				error("Error in St' production\n");
			}
			//node->addChild(tmp);
			print(tmp);
			mScanner->GetNextToken();
			VL(node->addChild("VL"));
			tmp = mScanner->GetNextToken();
			if(!tmp->isRB())
			{
				error("Error in St' production\n");
			}
			//node->addChild(tmp);
			print(tmp);
			tmp = mScanner->GetNextToken();
			if(!tmp->isRB())
			{
				error("Error in St' production\n");
			}
			//node->addChild(tmp);
			print(tmp);
		}
		else if(tmp->isStdout())
		{
			printmsg("St'->stdout O ]");
			//branch on operator
			node = node->addChild(tmp);
			print(tmp);
			O(node->addChild("O"));
			tmp = mScanner->GetNextToken();
			if(!tmp->isRB())
			{
				error("Error in St' production\n");
			}
			//node->addChild(tmp);
			print(tmp);
		}
	}
	else
	{
		error("Error in St' production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Stpp(Node* node)
{
	mIndent.append("\t");
	
	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isRB())
	{
		printmsg("St''->]");
		mScanner->GetNextToken();
		//node->addChild(tmp);
		print(tmp);
	}
	else
	{
		printmsg("St''->E]");
		E(node->addChild("E"));
		tmp = mScanner->GetNextToken();
		if(!tmp->isRB())
		{
			error("error in St'' production\n");
		}
		//node->addChild(tmp);
		print(tmp);
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::EL(Node* node)
{
	//mIndent.append("\t");
	printmsg("EL->E EL'");
	E(node->addChild("E"));
	ELp(node->addChild("EL'"));
	
	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::ELp(Node* node)
{
	//mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();

	if(tmp->isLB())
	{
		printmsg("EL'-> EL");
		//print(tmp);
		//mScanner->GetNextToken();
		EL(node->addChild("EL"));
	}
	else
	{
		printmsg("EL' -> empty");
	}

	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::VL(Node* node)
{
	mIndent.append("\t");
	printmsg("VL-> [ID Type] VL'");

	Token* tmp = mScanner->GetNextToken();
	if(!tmp->isLB())
	{
		error("Error in VL production\n");
	}
	//node->addChild(tmp);
	//print(tmp);
	tmp = mScanner->GetNextToken();
	if(!tmp->isID())
	{
		error("Error in VL Production\n");
	}
	node->addChild(tmp);
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!tmp->isTyp())
	{
		error("Error in VL Production\n");
	}
	node->addChild(tmp);
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!tmp->isRB())
	{
		error("Error in VL Production\n");
	}
	//node->addChild(tmp);
	print(tmp);
	VLp(node->addChild("VL'"));

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::VLp(Node* node)
{
	//mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(tmp->isLB())
	{
		printmsg("VL'->VL");
		VL(node->addChild("VL"));
	}
	else
	{
		printmsg("VL'->empty");
	}

	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::error(std::string msg)
{
	std::cout << msg;
	throw new std::exception();
}

void Parser::print(Token* token)
{
	std::cout << mIndent << token->GetLexeme() << std::endl;
}
