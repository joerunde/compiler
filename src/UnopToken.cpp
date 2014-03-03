#include "../include/UnopToken.h"
#include "../include/Node.h"


UnopToken::UnopToken(std::string lexeme):
	Token(lexeme)
{
}

UnopToken::~UnopToken(void)
{
}

std::string UnopToken::GetType()
{
	return("Unop");
}

Token* UnopToken::GetToken(std::string lexeme)
{
	return new UnopToken(lexeme);
}

bool UnopToken::isUnop()
{
	return true;
}

std::string UnopToken::GetLexeme(int type)
{
	std::string tmp = mLexeme;
	if(mLexeme == "not")
		tmp = "invert";
	if(mLexeme == "stdout" && type != Node::TYPE_STRING)
		tmp = "dup .\n";
	if(mLexeme == "stdout" && type == Node::TYPE_FLOAT)
		tmp = "dup f.\n";
	if(mLexeme == "stdout" && type == Node::TYPE_STRING)
		tmp = "2dup TYPE\n";

	if(type == Node::TYPE_FLOAT && mLexeme != "stdout")
	{
		std::string tmp2 = "f";
		tmp2.append(tmp);
		tmp = tmp2;
	}

	return tmp;
}