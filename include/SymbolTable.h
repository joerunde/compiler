#pragma once

#include <map>
#include <string>

//#include "Token.h"
class Token;

//Symbol table class for the compiler
//binary sorted table instead of hash at the moment
//this means no collisions, and performance is not a big concern of mine anyway

//implements two separate tables, one to be used for keywords, the other for identifiers
//identifiers can be added to the table, but keywords are set in the class definition

//tables store token pointers, so only a single token has to exist in the program for an ID or keyword

class SymbolTable
{
public:
	SymbolTable(void);
	~SymbolTable(void);

	Token* lookupIdentifier(std::string str);
	Token* lookupKeyword(std::string str);
	Token* lookupType(std::string str);

	void addIdentifier(std::string id, Token* token);

	void clearTables();

	void print();

private:
	std::map<std::string, Token*> mKeywords;
	std::map<std::string, Token*> mIdentifiers;
	std::map<std::string, Token*> mTypes;
};

