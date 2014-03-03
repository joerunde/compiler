#include "../include/BinopToken.h"
#include "../include/Node.h"

BinopToken::BinopToken(std::string lexeme):
	Token(lexeme)
{
}

BinopToken::~BinopToken(void)
{
}

std::string BinopToken::GetType()
{
	return("Binop");
}

Token* BinopToken::GetToken(std::string lexeme)
{
	return new BinopToken(lexeme);
}

bool BinopToken::isBinop()
{
	return true;
}

std::string BinopToken::GetLexeme(int type)
{
	std::string tmp = mLexeme;
	if(mLexeme == "!=")
		tmp = "<>";
	if(mLexeme == "%")
		tmp = "mod";
	if(type == Node::TYPE_STRING && mLexeme == "+")
		tmp = "append";
	if(mLexeme == "^")
		tmp = "**";

	if(type == Node::TYPE_FLOAT)
	{
		std::string tmp2 = "f";
		tmp2.append(tmp);
		tmp = tmp2;
	}

	return tmp;
}

int BinopToken::GetReturnType(int type)
{
	if(mLexeme == ">" || mLexeme == "<" || mLexeme == ">=" || mLexeme == "<=" || mLexeme == "==" || mLexeme == "!=")
		return Node::TYPE_BOOL;
	return type;
}