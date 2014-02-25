#--------------------------------------------
# INSTRUCTION
# Quoted strings are to be filled in by student
#
CCC = clang++
CCFLAGS =
OBJS = Automaton.o BinopToken.o BoolToken.o BracketToken.o FloatToken.o IBTLAutomaton.o IDToken.o IntegerToken.o KeywordToken.o Parser.o main.o Scanner.o StrToken.o SymbolTable.o Token.o TypToken.o UnopToken.o
SOURCE = src/Automaton.cpp src/BinopToken.cpp src/BoolToken.cpp src/BracketToken.cpp src/FloatToken.cpp src/IBTLAutomaton.cpp src/IDToken.cpp src/IntegerToken.cpp src/KeywordToken.cpp src/Parser.cpp src/main.cpp src/Scanner.cpp src/StrToken.cpp src/SymbolTable.cpp src/Token.cpp src/TypToken.cpp src/UnopToken.cpp src/Node.cpp
RUNFLAGS = 
TESTFLAGS = a.in b.in c.in d.in e.in f.in g.in h.in j.in k.in l.in m.in n.in o.in p.in q.in r.in s.in t.in u.in v.in w.in x.in y.in z.in

$(OBJS): $(SOURCE)
	$(CCC) $(CCFLAGS) -c $(SOURCE)

compiler: $(OBJS)
	$(CCC) $(CCFLAGS) -o compiler $(OBJS)

clean:
	rm -f *.o *.out
	ls

stutest.out: compiler
	-./compiler $(RUNFLAGS) $(TESTFLAGS) > stutest1.out
	cat stutest1.out

proftest.out: compiler
	cat $(PROFTEST)
	compiler $(PROFTEST) > proftest.out
	cat proftest.out
