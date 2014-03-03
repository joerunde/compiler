#include "../include/IBTLAutomaton.h"
#include "../include/Tokens.h"


IBTLAutomaton::IBTLAutomaton()
{
	//construction of the IBTL DFA

	/* Brackets */
	mStateMap[0].insert('[');
	mStateMap[0].insert(']');
	mTransitionMap[0]['['] = 1;
	mTransitionMap[0][']'] = 1;
	mAcceptStatesNoPush.insert(1);
	mAcceptTokens[1] = new BracketToken("");

	/* Strings*/ 
	mStateMap[0].insert('"');
	mStateMap[2].insert('"');
	mTransitionMap[0]['"'] = 2;
	mElseMap[2] = 2;
	mTransitionMap[2]['"'] = 3;
	mAcceptStatesNoPush.insert(3);
	mAcceptTokens[3] = new StrToken("");

	/* Ints and Reals */
	for(char c = '0'; c <= '9'; c++)
	{
		mStateMap[0].insert(c);
		mTransitionMap[0][c] = 4;
		mStateMap[4].insert(c);
		mStateMap[6].insert(c);
		mStateMap[7].insert(c);
		mTransitionMap[7][c] = 10;
		mStateMap[10].insert(c);
		mStateMap[35].insert(c);
		mTransitionMap[35][c] = 10;

		//negative constants
		mStateMap[37].insert(c);
		mTransitionMap[37][c] = 4;
		//for IDs
		mStateMap[32].insert(c);
	}
	mStateMap[0].insert('.');
	mStateMap[4].insert('.');
	mStateMap[37].insert('.');
	mStateMap[4].insert('e');
	mStateMap[6].insert('e');
	mStateMap[7].insert('-');
	mStateMap[35].insert('-');
	mTransitionMap[4]['.'] = 6;
	mTransitionMap[0]['.'] = 6;
	mTransitionMap[37]['.'] = 6;
	mTransitionMap[4]['e'] = 35;
	mTransitionMap[6]['e'] = 7;
	mTransitionMap[7]['-'] = 10;
	mTransitionMap[35]['-'] = 10;
	mElseMap[4] = 5;
	mElseMap[35] = 36;
	mElseMap[37] = 12;
	mAcceptPushTwoStates.insert(36);
	mAcceptTokens[36] = new IntegerToken("");
	mAcceptPushOneStates.insert(5);
	mAcceptTokens[5] = new IntegerToken("");
	mElseMap[6] = 9;
	mAcceptPushOneStates.insert(9);
	mAcceptTokens[9] = new FloatToken("");
	mElseMap[7] = 8;
	mAcceptPushTwoStates.insert(8);
	mAcceptTokens[8] = new FloatToken("");
	mElseMap[10] = 9;

	/* Binops */
	mStateMap[0].insert('<');
	mStateMap[0].insert('>');
	mStateMap[0].insert(':');
	mStateMap[0].insert('!');
	mStateMap[0].insert('+');
	mStateMap[0].insert('-');
	mStateMap[0].insert('*');
	mStateMap[0].insert('/');
	mStateMap[0].insert('%');
	mStateMap[0].insert('^');
	mStateMap[0].insert('=');
	mStateMap[0].insert('o');
	mStateMap[0].insert('a');
	mStateMap[0].insert('O');
	mStateMap[0].insert('A');

	mTransitionMap[0]['<'] = 11;
	mTransitionMap[0]['>'] = 11;
	mTransitionMap[0][':'] = 13;
	mTransitionMap[0]['!'] = 13;
	mTransitionMap[0]['+'] = 14;
	mTransitionMap[0]['-'] = 37;//can also be number
	mTransitionMap[0]['*'] = 14;
	mTransitionMap[0]['/'] = 14;
	mTransitionMap[0]['%'] = 14;
	mTransitionMap[0]['^'] = 14;
	mTransitionMap[0]['='] = 14;


	mAcceptStatesNoPush.insert(14);
	mAcceptTokens[14] = new BinopToken("");

	mStateMap[13].insert('=');
	mStateMap[11].insert('=');
	mElseMap[11] = 12;
	mAcceptPushOneStates.insert(12);
	mAcceptTokens[12] = new BinopToken("");
	mTransitionMap[11]['='] = 14;
	mTransitionMap[13]['='] = 14;

	/* Stuff for rest of binops, unops, bools, and IDs */
	for(char c = 'A'; c <= 'z'; c++)
	{
		if(c > 'Z' && c < 'a')
			continue;

		mStateMap[0].insert(c);
		mStateMap[15].insert(c);
		mStateMap[16].insert(c);
		mStateMap[17].insert(c);
		mStateMap[18].insert(c);
		mStateMap[19].insert(c);
		mStateMap[21].insert(c);
		mStateMap[22].insert(c);
		mStateMap[23].insert(c);
		mStateMap[24].insert(c);
		mStateMap[25].insert(c);
		mStateMap[26].insert(c);
		mStateMap[27].insert(c);
		mStateMap[28].insert(c);
		mStateMap[29].insert(c);
		mStateMap[30].insert(c);
		mStateMap[32].insert(c);
		mStateMap[34].insert(c);

		mTransitionMap[0][c] = 32;
		mTransitionMap[15][c] = 32;
		mTransitionMap[16][c] = 32;
		mTransitionMap[17][c] = 32;
		mTransitionMap[18][c] = 32;
		mTransitionMap[19][c] = 32;
		mTransitionMap[21][c] = 32;
		mTransitionMap[22][c] = 32;
		mTransitionMap[23][c] = 32;
		mTransitionMap[24][c] = 32;
		mTransitionMap[25][c] = 32;
		mTransitionMap[26][c] = 32;
		mTransitionMap[27][c] = 32;
		mTransitionMap[28][c] = 32;
		mTransitionMap[29][c] = 32;
		mTransitionMap[30][c] = 32;
		mTransitionMap[34][c] = 32;
	}
	
	mTransitionMap[0]['o'] = 15;
	mTransitionMap[0]['a'] = 16;
	mTransitionMap[0]['O'] = 15;
	mTransitionMap[0]['A'] = 16;
	mTransitionMap[15]['r'] = 14;
	mTransitionMap[15]['R'] = 14;
	mElseMap[15] = 33;
	mTransitionMap[16]['n'] = 17;
	mTransitionMap[16]['N'] = 17;
	mElseMap[16] = 33;
	mTransitionMap[17]['d'] = 14;
	mTransitionMap[17]['D'] = 14;
	mElseMap[17] = 33;

	mTransitionMap[0]['s'] = 18;
	mTransitionMap[0]['S'] = 18;
	mTransitionMap[18]['i'] = 19;
	mTransitionMap[18]['I'] = 19;
	mElseMap[18] = 33;
	mTransitionMap[19]['n'] = 20;
	mTransitionMap[19]['N'] = 20;
	mElseMap[19] = 33;
	mTransitionMap[0]['c'] = 21;
	mTransitionMap[0]['C'] = 21;
	mTransitionMap[21]['o'] = 22;
	mTransitionMap[21]['O'] = 22;
	mElseMap[21] = 33;
	mTransitionMap[22]['s'] = 20;
	mTransitionMap[22]['S'] = 20;
	mElseMap[22] = 33;
	mTransitionMap[0]['n'] = 23;
	mTransitionMap[0]['N'] = 23;
	mTransitionMap[23]['o'] = 24;
	mTransitionMap[23]['O'] = 24;
	mElseMap[23] = 33;
	mTransitionMap[24]['t'] = 20;
	mTransitionMap[24]['T'] = 20;
	mElseMap[24] = 33;
	mTransitionMap[0]['t'] = 25;
	mTransitionMap[0]['T'] = 25;
	mTransitionMap[25]['r'] = 26;
	mTransitionMap[25]['R'] = 26;
	mElseMap[25] = 33;
	mTransitionMap[26]['u'] = 27;
	mTransitionMap[26]['U'] = 27;
	mElseMap[26] = 33;
	mTransitionMap[27]['e'] = 31;
	mTransitionMap[27]['E'] = 31;
	mElseMap[27] = 33;
	mTransitionMap[0]['f'] = 28;
	mTransitionMap[0]['F'] = 28;
	mTransitionMap[28]['a'] = 29;
	mTransitionMap[28]['A'] = 29;
	mElseMap[28] = 33;
	mTransitionMap[29]['l'] = 30;
	mTransitionMap[29]['L'] = 30;
	mElseMap[29] = 33;
	mTransitionMap[30]['S'] = 27;
	mTransitionMap[30]['s'] = 27;
	mElseMap[30] = 33;
	mTransitionMap[25]['a'] = 34;
	mTransitionMap[25]['A'] = 34;
	mElseMap[25] = 33;
	mTransitionMap[34]['n'] = 20;
	mTransitionMap[34]['N'] = 20;
	mElseMap[34] = 33;


	mElseMap[32] = 33;
	mAcceptPushOneStates.insert(33);
	mAcceptTokens[33] = new IDToken("");

	mAcceptStatesNoPush.insert(20);
	mAcceptTokens[20] = new UnopToken("");
	mAcceptStatesNoPush.insert(31);
	mAcceptTokens[31] = new BoolToken("");

}


IBTLAutomaton::~IBTLAutomaton()
{
}
