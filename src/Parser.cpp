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

void Parser::Parse()
{
	mIndent.clear();
	try{
		T();
	}catch(...)
	{
		std::cout << "\nparser barfed\n\n";
		//nothing, just quit
	}
}

void Parser::T()
{
	std::cout << "\n";
	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("T->[S]");
		print(tmp);
		mScanner->GetNextToken();
		S();
		tmp = mScanner->PeekOneToken();
		if(!isRB(tmp))
		{
			error("Error in T production\n");
		}
		print(tmp);
		mScanner->GetNextToken();
	}
}

void Parser::S()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	Token* tmp2 = mScanner->PeekTwoTokens();
	if( isLB(tmp) && (isLB(tmp2) || isRB(tmp2) || isConstant(tmp2) || isID(tmp2) ) )
	{
		printmsg("S->[S'S''");
		print(tmp);
		mScanner->GetNextToken();
		Sp();
		Spp();
	}
	else
	{
		printmsg("S->ES''");
		E();
		Spp();
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Sp()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isRB(tmp))
	{
		printmsg("S'->]");
		print(tmp);
		mScanner->GetNextToken();
	}
	else
	{
		printmsg("S'->S]");
		S();
		tmp = mScanner->PeekOneToken();
		if(!isRB(tmp))
		{
			error("Error in S' production\n");
		}
		print(tmp);
		mScanner->GetNextToken();
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Spp()
{
	Token* tmp = mScanner->PeekOneToken();
	if(!isRB(tmp))
	{
		printmsg("S''->SS''");
		S();
		Spp();
	}
	else
		printmsg("S''->empty");
}

void Parser::E()
{
	//mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	Token* tmp2 = mScanner->PeekTwoTokens();
	if(isConstant(tmp) || isID(tmp))
	{
		printmsg("E->O");
		O();
	}
	else if(isLB(tmp) && ( isUnop(tmp2) || isBinop(tmp2) ) )
	{
		printmsg("E->O");
		O();
	}
	else
	{
		printmsg("E->St");
		St();
	}

	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::O()
{
	mIndent.append("\t");
	
	Token* tmp = mScanner->PeekOneToken();

	if(isConstant(tmp) || isID(tmp))
	{
		printmsg("O->ID|constant");
		print(tmp);
		mScanner->GetNextToken();
	}
	else if(isLB(tmp))
	{
		printmsg("O->[O'");
		print(tmp);
		mScanner->GetNextToken();
		Op();
	}
	else
	{
		error("Error in O production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Op()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isAssign(tmp))
	{
		printmsg("O'->:= ID O]");
		print(tmp);
		mScanner->GetNextToken();
		tmp = mScanner->PeekOneToken();
		if(!isID(tmp))
		{
			error("Error in O' production\n");
		}
		print(tmp);
		mScanner->GetNextToken();
		O();
	}
	else if(isUnop(tmp))
	{
		printmsg("O->Unop O]");
		print(tmp);
		mScanner->GetNextToken();
		O();
	}
	else if(isBinop(tmp))
	{
		printmsg("O->Binop O O]");
		print(tmp);
		mScanner->GetNextToken();
		O();
		O();
	}

	//common to all productions
	tmp = mScanner->PeekOneToken();
	if(!isRB(tmp))
	{
		error("Error in O' production\n");
	}
	print(tmp);
	mScanner->GetNextToken();

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::St()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("St->[St'");
		print(tmp);
		mScanner->GetNextToken();
		Stp();
	}
	else
	{
		error("Error in St production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Stp()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isKeyword(tmp))
	{
		mScanner->GetNextToken();
		if(isWhile(tmp))
		{
			printmsg("St'->while E EL ]");
			print(tmp);
			E();
			EL();
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			print(tmp);
		}
		else if(isIf(tmp))
		{
			printmsg("St'->if E E St''");
			print(tmp);
			E();
			E();
			Stpp();
		}
		else if(isLet(tmp))
		{
			printmsg("St'->let [VL] ]");
			print(tmp);
			tmp = mScanner->PeekOneToken();
			if(!isLB(tmp))
			{
				error("Error in St' production\n");
			}
			print(tmp);
			mScanner->GetNextToken();
			VL();
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			print(tmp);
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			print(tmp);
		}
		else if(isStdout(tmp))
		{
			printmsg("St'->stdout O ]");
			print(tmp);
			O();
			tmp = mScanner->GetNextToken();
			if(!isRB(tmp))
			{
				error("Error in St' production\n");
			}
			print(tmp);
		}
	}
	else
	{
		error("Error in St' production\n");
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::Stpp()
{
	mIndent.append("\t");
	
	Token* tmp = mScanner->PeekOneToken();
	if(isRB(tmp))
	{
		printmsg("St''->]");
		mScanner->GetNextToken();
		print(tmp);
	}
	else
	{
		printmsg("St''->E]");
		E();
		tmp = mScanner->GetNextToken();
		if(!isRB(tmp))
		{
			error("error in St'' production\n");
		}
		print(tmp);
	}

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::EL()
{
	//mIndent.append("\t");
	printmsg("EL->E EL'");
	E();
	ELp();
	
	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::ELp()
{
	//mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();

	if(isLB(tmp))
	{
		printmsg("EL'-> EL");
		//print(tmp);
		//mScanner->GetNextToken();
		EL();
	}
	else
	{
		printmsg("EL' -> empty");
	}

	//mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::VL()
{
	mIndent.append("\t");
	printmsg("VL-> [ID Type] VL'");

	Token* tmp = mScanner->GetNextToken();
	if(!isLB(tmp))
	{
		error("Error in VL production\n");
	}
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isID(tmp))
	{
		error("Error in VL Production\n");
	}
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isTyp(tmp))
	{
		error("Error in VL Production\n");
	}
	print(tmp);
	tmp = mScanner->GetNextToken();
	if(!isRB(tmp))
	{
		error("Error in VL Production\n");
	}
	VLp();

	mIndent.erase(mIndent.end()-1, mIndent.end());
}

void Parser::VLp()
{
	mIndent.append("\t");

	Token* tmp = mScanner->PeekOneToken();
	if(isLB(tmp))
	{
		printmsg("VL'->VL");
		VL();
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
