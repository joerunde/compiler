#--------------------------------------------
# INSTRUCTION
# Quoted strings are to be filled in by student
#
CCC = g++
CCFLAGS =
OBJS = Automaton.o BinopToken.o BoolToken.o BracketToken.o FloatToken.o IDToken.o IntegerToken.o KeywordToken.o main.o Scanner.o StrToken.o Token.o UnopToken.o
SOURCE = src/Automaton.cpp src/BinopToken.cpp src/BoolToken.cpp src/BracketToken.cpp src/FloatToken.cpp src/IDToken.cpp src/IntegerToken.cpp src/KeywordToken.cpp src/main.cpp src/Scanner.cpp src/StrToken.cpp src/Token.cpp src/UnopToken.cpp
RUNFLAGS = 

$(OBJS): $(SOURCE)
	$(CCC) $(CCFLAGS) -c $(SOURCE)

compiler: $(OBJS)
	$(CCC) $(CCFLAGS) -o compiler $(OBJS)

clean:
	rm -f Automaton.o BinopToken.o BoolToken.o BracketToken.o FloatToken.o IDToken.o IntegerToken.o KeywordToken.o main.o Scanner.o StrToken.o Token.o UnopToken.o core compiler.o stutest1.out stutest2.out proftest.out
	ls

stutest.out: compiler
	cat stutest1.in
	-./compiler $(RUNFLAGS) stutest1.in > stutest1.out
	cat stutest1.out
# Notice the next line. The `-' says to ignore the return code. This
# is a way to have multiple tests of errors that cause non-zero return
# codes.
	cat stutest2.in
	-./compiler stutest2.in > stutest2.out
	cat stutest2.out

proftest.out: compiler
	cat $(PROFTEST)
	compiler $(PROFTEST) > proftest.out
	cat proftest.out

