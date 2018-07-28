CC = g++
CFLAGS = -Wall -std=c++11

all: main.exe
unittest: test.exe

# to test without particular component, remove dependency by removing *.o when linking
main.exe: main.cpp Parser.o Lexer.o Interpreter.o EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o main.cpp EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o

test.exe: main.cpp Parser.o Lexer.o Interpreter.o EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o .\_UnitTests\UnitTest1.cpp EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o

Interpreter.o: Parser/Parser.hpp Lexer/Lexer.hpp
	$(CC) $(CFLAGS) -o $@ -c Interpreter/Interpreter.cpp

Parser.o: Parser/Parser.cpp Parser/Parser.hpp
	$(CC) $(CFLAGS) -o $@ -c Parser/Parser.cpp

Lexer.o: Lexer/Lexer.cpp Lexer/Lexer.hpp BasicInterface/DebugUtility.hpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/Lexer.cpp

EOF_Token.o: Lexer/EOF_Token.cpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/EOF_Token.cpp

IntegerToken.o: Lexer/IntegerToken.cpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/IntegerToken.cpp

StringToken.o: Lexer/StringToken.cpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/StringToken.cpp

TokenFactory.o: Lexer/TokenFactory.cpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/TokenFactory.cpp

clean:
	del *.exe *.o