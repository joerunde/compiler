#include "../include/Automaton.h"
#include "../include/Token.h"
#include "../include/Tokens.h"
#include "../include/Scanner.h"

#include <iostream>


int main(int argc, char **argv)
{
	Scanner scanner;

	//uncomment for user to type in files
	/*std::string s;
	do
	{
		std::cout << "\nFile: ";
		std::getline(std::cin, s);

		scanner.ScanFile(s);

	}while(s != std::string("quit"));*/

	std::string f = argv[1];
	scanner.ScanFile(f);

	return 0;
}
