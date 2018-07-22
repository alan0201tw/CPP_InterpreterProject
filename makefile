CC = g++
CFLAGS = -Wall

all: Interpreter.exe

Interpreter.exe: Parser.o Lexer.o Interpreter.o
	$(CC) $(CFLAGS) -o $@ Parser.o Lexer.o Interpreter.o

Interpreter.o: Interpreter.cpp Parser/Parser.hpp Lexer/Lexer.hpp
	$(CC) $(CFLAGS) -o $@ -c Interpreter.cpp

Parser.o: Parser/Parser.cpp Parser/Parser.hpp
	$(CC) $(CFLAGS) -o $@ -c Parser/Parser.cpp

Lexer.o: Lexer/Lexer.cpp Lexer/Lexer.hpp BasicInterface/DebugUtility.hpp
	$(CC) $(CFLAGS) -o $@ -c Lexer/Lexer.cpp

clean:
	del Interpreter.exe *.o