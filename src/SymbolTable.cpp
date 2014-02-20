#include "../include/SymbolTable.h"
#include "../include/KeywordToken.h"
#include "../include/TypToken.h"
#include <iostream>


SymbolTable::SymbolTable(void)
{
	clearTables();
}

SymbolTable::~SymbolTable(void)
{
}

Token* SymbolTable::lookupIdentifier(std::string str)
{
	if(mIdentifiers.count(str) > 0)
	{
		return mIdentifiers[str];
	}
	return 0;
}

Token* SymbolTable::lookupKeyword(std::string str)
{
	if(mKeywords.count(str) > 0)
	{
		return mKeywords[str];
	}
	return 0;
}

Token* SymbolTable::lookupType(std::string str)
{
	if(mTypes.count(str) > 0)
	{
		return mTypes[str];
	}
	return 0;
}

void SymbolTable::addIdentifier(std::string str, Token* token)
{
	mIdentifiers[str] = token;
}

void SymbolTable::clearTables()
{
	mIdentifiers.clear();
	mKeywords.clear();
	mTypes.clear();
	mKeywords["while"] = new KeywordToken("while");
	mKeywords["if"] = new KeywordToken("if");
	mKeywords["let"] = new KeywordToken("let");
	mKeywords["for"] = new KeywordToken("for");
	mKeywords["stdout"] = new KeywordToken("stdout");
	mTypes["bool"] = new TypToken("bool");
	mTypes["int"] = new TypToken("int");
	mTypes["float"] = new TypToken("float");
	mTypes["string"] = new TypToken("string");
}

void SymbolTable::print()
{
	std::cout << "\nSymbol Table----------\n";
	int i = 0;
	std::map<std::string, Token*>::iterator c;
	for(c = mKeywords.begin(); c != mKeywords.end(); c++)
	{
		std::cout << i++ << "-  " << c->first << "\n";
	}
	std::cout << "\n";
	i = 0;
	for(c = mIdentifiers.begin(); c != mIdentifiers.end(); c++)
	{
		std::cout << i++ << "-  " << c->first << "\n";
	}
	std::cout << "\n\n";
}