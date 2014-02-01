#include "../include/Automaton.h"
#include "../include/Token.h"
#include "../include/Tokens.h"
#include "../include/Scanner.h"

#include <iostream>


void main()
{
	Scanner scanner;

	std::string s;
	do
	{
		std::cout << "\nFile: ";
		std::getline(std::cin, s);

		scanner.ScanFile(s);

	}while(s != std::string("quit"));
	
	//tStateMap states;
	//tTransitionMap transitions;
	//std::set<int> acceptStates;

	//for(char c = 'a'; c <= 'z'; c++)
	//{
	//	states[0].insert(c);
	//	states[1].insert(c);
	//	transitions[0][c] = 1;
	//}
	//for(char c = 'A'; c <= 'Z'; c++)
	//{
	//	states[0].insert(c);
	//	states[1].insert(c);
	//	transitions[0][c] = 1;
	//}
	//for(char c = '0'; c <= '9'; c++)
	//{
	//	states[1].insert(c);
	//}
	//
	//acceptStates.insert(1);

	//Automaton identifiers(states, transitions, acceptStates);

	//identifiers.ResetAutomata();

	//std::cout << identifiers.ProcessChar('a');
	//std::cout << identifiers.ProcessChar('b');
	//std::cout << identifiers.ProcessChar('1');
	//std::cout << identifiers.ProcessChar('2') << std::endl;
	//identifiers.ResetAutomata();
	//std::cout << identifiers.ProcessChar('A');
	//std::cout << identifiers.ProcessChar('Z') << std::endl;
	//identifiers.ResetAutomata();
	//std::cout << identifiers.ProcessChar('1');
	//std::cout << identifiers.ProcessChar('Z') << std::endl;
	//identifiers.ResetAutomata();
	//std::cout << identifiers.ProcessChar('A');
	//std::cout << identifiers.ProcessChar('/') << std::endl;

	std::cin.get();
}