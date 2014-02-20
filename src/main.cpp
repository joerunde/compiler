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

	//uncomment for user to type in files
	std::string s;
	do
	{
		std::cout << "\nFile: ";
		std::getline(std::cin, s);

		if(!scanner.OpenFile(s))
			continue;

		parser.Parse();
		/*Token* temp;
		while((temp = scanner.GetNextToken()) != 0)
		{
			std::cout << "(" << temp->GetType() << ", " << temp->GetLexeme() << ")";
		}*/


		scanner.CloseFile();

		//table->print();

		table->clearTables();
	}while(s != std::string("quit"));

	//std::string f = argv[1];
	//scanner.ScanFile(f);

	return 0;
}
