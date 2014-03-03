#include "../include/IDToken.h"
#include "../include/KeywordToken.h"
#include "../include/UnopToken.h"
#include "../include/SymbolTable.h"

IDToken::IDToken(std::string lexeme):
	Token(lexeme)
{
}


IDToken::~IDToken(void)
{
}

std::string IDToken::GetType()
{
	return("Identifier");
}

Token* IDToken::GetToken(std::string lexeme)
{
	if(lexeme == "stdout")
		return new UnopToken(lexeme);
	Token* temp = sSymTable->lookupKeyword(lexeme);
	if(temp)
		return temp;
	temp = sSymTable->lookupType(lexeme);
	if(temp)
		return temp;
	temp = sSymTable->lookupIdentifier(lexeme);
	if(temp)
		return temp;
	temp = new IDToken(lexeme);
	sSymTable->addIdentifier(lexeme, temp);
	return temp;
}

bool IDToken::isID()
{
	return true;
}

