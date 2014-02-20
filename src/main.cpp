#include "../include/Automaton.h"
#include "../include/Token.h"
#include "../include/Tokens.h"
#include "../include/Scanner.h"
#include "../include/SymbolTable.h"
#include "../include/Parser.h"
#include <iostream>

int main(int argc, char **argv)
{
	Scanner scanner;
	SymbolTable* table = new SymbolTable();
	scanner.setTable(table);
	Parser parser;
	parser.SetScanner(&scanner);
	parser.SetSymbolTable(table);

	int c = 1;
	std::string s;
	do
	{
		if(c < argc)
		{
			s = argv[c];
			c++;
		}
		else
		{
			std::cout << "\nFile: ";
			std::getline(std::cin, s);
		}

		if(!scanner.OpenFile(s))
			continue;

		parser.Parse();

		//print tokens from scanner
		/*Token* temp;
		while((temp = scanner.GetNextToken()) != 0)
		{
			std::cout << "(" << temp->GetType() << ", " << temp->GetLexeme() << ")";
		}*/


		scanner.CloseFile();

		//print symbol table
		//table->print();

		table->clearTables();
	}while(s != std::string("quit"));


	return 0;
}
