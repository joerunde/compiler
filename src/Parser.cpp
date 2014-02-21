#include "../include/Parser.h"
#include "../include/SymbolTable.h"
#include "../include/Tokens.h"
#include "../include/Scanner.h"
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
	return parsetree;
}

void Parser::T(Node* node)
{
	std::cout << "\n";
	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("T->[S]");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		S(node->addChild("S"));
		tmp = mScanner->PeekOneToken();
		if(!isRB(tmp))
		{
			error("Error in T production\n");
		}
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}
}

void Parser::S(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	Token* tmp2 = mScanner->PeekTwoTokens();
	if( isLB(tmp) && (isLB(tmp2) || isRB(tmp2) || isConstant(tmp2) || isID(tmp2) ) )
	{
		printmsg("S->[S'S''");
		node->addChild(tmp);
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
	if(isRB(tmp))
	{
		printmsg("S'->]");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}
	else
	{
		printmsg("S'->S]");
		S(node->addChild("S"));
		tmp = mScanner->PeekOneToken();
		if(!isRB(tmp))
		{
			error("Error in S' production\n");
		}
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Spp(Node* node)
{
	Token* tmp = mScanner->PeekOneToken();
	if(!isRB(tmp))
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
	if(isConstant(tmp) || isID(tmp))
	{
		printmsg("E->O");
		O(node->addChild("O"));
	}
	else if(isLB(tmp) && ( isUnop(tmp2) || isBinop(tmp2) ) )
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

	if(isConstant(tmp) || isID(tmp))
	{
		printmsg("O->ID|constant");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
	}
	else if(isLB(tmp))
	{
		printmsg("O->[O'");
		node->addChild(tmp);
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
	if(isAssign(tmp))
	{
		printmsg("O'->:= ID O]");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		tmp = mScanner->PeekOneToken();
		if(!isID(tmp))
		{
			error("Error in O' production\n");
		}
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
	}
	else if(isUnop(tmp))
	{
		printmsg("O->Unop O]");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
	}
	else if(isBinop(tmp))
	{
		printmsg("O->Binop O O]");
		node->addChild(tmp);
		print(tmp);
		mScanner->GetNextToken();
		O(node->addChild("O"));
		O(node->addChild("O"));
	}

	//common to all productions
	tmp = mScanner->PeekOneToken();
	if(!isRB(tmp))
	{
		error("Error in O' production\n");
	}
	node->addChild(tmp);
	print(tmp);
	mScanner->GetNextToken();

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::St(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("St->[St'");
		node->addChild(tmp);
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
	if(isKeyword(tmp))
	{
		mScanner->GetNextToken();
		if(isWhile(tmp))
		{
			printmsg("St'->while E EL ]");
			node->addChild(tmp);
			print(tmp);
			E(node->addChild("E"));
			EL(node->addChild("EL"));
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			node->addChild(tmp);
			print(tmp);
		}
		else if(isIf(tmp))
		{
			printmsg("St'->if E E St''");
			node->addChild(tmp);
			print(tmp);
			E(node->addChild("E"));
			E(node->addChild("E"));
			Stpp(node->addChild("Stpp"));
		}
		else if(isLet(tmp))
		{
			printmsg("St'->let [VL] ]");
			node->addChild(tmp);
			print(tmp);
			tmp = mScanner->PeekOneToken();
			if(!isLB(tmp))
			{
				error("Error in St' production\n");
			}
			node->addChild(tmp);
			print(tmp);
			mScanner->GetNextToken();
			VL(node->addChild("VL"));
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			node->addChild(tmp);
			print(tmp);
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			node->addChild(tmp);
			print(tmp);
		}
		else if(isStdout(tmp))
		{
			printmsg("St'->stdout O ]");
			node->addChild(tmp);
			print(tmp);
			O(node->addChild("O"));
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			node->addChild(tmp);
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
	if(isRB(tmp))
	{
		printmsg("St''->]");
		mScanner->GetNextToken();
		node->addChild(tmp);
		print(tmp);
	}
	else
	{
		printmsg("St''->E]");
		E(node->addChild("E"));
		tmp = mScanner->GetNextToken();
		if(!isRB(tmp))
		{
			error("error in St'' production\n");
		}
		node->addChild(tmp);
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

	if(isLB(tmp))
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
	if(!isLB(tmp))
	{
		error("Error in VL production\n");
	}
	node->addChild(tmp);
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isID(tmp))
	{
		error("Error in VL Production\n");
	}
	node->addChild(tmp);
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isTyp(tmp))
	{
		error("Error in VL Production\n");
	}
	node->addChild(tmp);
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isRB(tmp))
	{
		error("Error in VL Production\n");
	}
	node->addChild(tmp);
	print(tmp);
	VLp(node->addChild("VL'"));

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::VLp(Node* node)
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("VL'->VL");
		VL(node->addChild("VL"));
	}
	else
	{
		printmsg("VL'->empty");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
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

bool Parser::isRB(Token* token)
{
	if(typeid(*token) == typeid(BracketToken))
	{
		if(token->GetLexeme() == "]")
			return true;
	}
	return false;
}

bool Parser::isLB(Token* token)
{
	if(typeid(*token) == typeid(BracketToken))
	{
		if(token->GetLexeme() == "[")
			return true;
	}
	return false;
}

bool Parser::isConstant(Token* token)
{
	if(isInt(token) || isReal(token) || isBool(token) || isStr(token) )
		return true;
	return false;
}

bool Parser::isInt(Token* token)
{
	if(typeid(*token) == typeid(IntegerToken))
		return true;
	return false;
}

bool Parser::isID(Token* token)
{
	if(typeid(*token) == typeid(IDToken))
		return true;
	return false;
}

bool Parser::isReal(Token* token)
{
	if(typeid(*token) == typeid(FloatToken))
		return true;
	return false;
}

bool Parser::isBool(Token* token)
{
	if(typeid(*token) == typeid(BoolToken))
		return true;
	return false;
}

bool Parser::isStr(Token* token)
{
	if(typeid(*token) == typeid(StrToken))
		return true;
	return false;
}

bool Parser::isAssign(Token* token)
{
	if(isBinop(token) && token->GetLexeme() == ":=")
		return true;
	return false;
}

bool Parser::isUnop(Token* token)
{
	if(typeid(*token) == typeid(UnopToken))
		return true;
	return false;
}

bool Parser::isBinop(Token* token)
{
	if(typeid(*token) == typeid(BinopToken))
		return true;
	return false;
}
	
bool Parser::isTyp(Token* token)
{
	if(typeid(*token) == typeid(TypToken))
		return true;
	return false;
}

bool Parser::isKeyword(Token* token)
{
	if(typeid(*token) == typeid(KeywordToken))
		return true;
	return false;
}

bool Parser::isWhile(Token* token)
{
	if(isKeyword(token) && token->GetLexeme() == "while")
		return true;
	return false;
}

bool Parser::isLet(Token* token)
{
	if(isKeyword(token) && token->GetLexeme() == "let")
		return true;
	return false;
}

bool Parser::isIf(Token* token)
{
	if(isKeyword(token) && token->GetLexeme() == "if")
		return true;
	return false;
}

bool Parser::isStdout(Token* token)
{
	if(isKeyword(token) && token->GetLexeme() == "stdout")
		return true;
	return false;
}
