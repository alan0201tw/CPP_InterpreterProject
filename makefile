CC = g++
CFLAGS = -Wall -std=c++11

all: main.exe
# to test without particular component, remove dependency by removing *.o when linking
main.exe: main.cpp Parser.o Lexer.o Interpreter.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o main.cpp

Interpreter.o: Parser/Parser.hpp Lexer/Lexer.hpp
	$(CC) $(CFLAGS) -o $@ -c Interpreter/Interpreter.cpp

Parser.o: Parser/Parser.cpp Parser/Parser.hpp
	$(CC) $(CFLAGS) -o $@ -c Parser/Parser.cpp

Lexer.o: Lexer/Lexer.cpp Lexer/Lexer.hpp BasicInterface/DebugUtility.hpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/Lexer.cpp

clean:
	del main.exe *.o