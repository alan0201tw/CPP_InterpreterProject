CC = g++
CFLAGS = -Wall -std=c++11

all: main.exe
unittest: test.exe

# to test without particular component, remove dependency by removing *.o when linking
main.exe: main.cpp Parser.o Lexer.o Interpreter.o EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o main.cpp EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o

test.exe: main.cpp Parser.o Lexer.o Interpreter.o EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o .\_UnitTests\UnitTest1.cpp EOF_Token.o IntegerToken.o StringToken.o TokenFactory.o

Interpreter.o:
	$(CC) $(CFLAGS) -o $@ -c src/Interpreter.cpp

Parser.o:
	$(CC) $(CFLAGS) -o $@ -c src/Parser.cpp

Lexer.o:
	$(CC) $(CFLAGS) -o $@ -c src/Lexer.cpp

EOF_Token.o:
	$(CC) $(CFLAGS) -o $@ -c src/EOF_Token.cpp

IntegerToken.o:
	$(CC) $(CFLAGS) -o $@ -c src/IntegerToken.cpp

StringToken.o:
	$(CC) $(CFLAGS) -o $@ -c src/StringToken.cpp

TokenFactory.o:
	$(CC) $(CFLAGS) -o $@ -c src/TokenFactory.cpp

clean:
	del *.exe *.o