WhitespaceInterpreter.out : Command.o
	g++ -Wall Command.o Main.cpp -o WhitespaceInterpreter.out

Command.o : Command.cpp Command.h
	g++ -Wall -c Command.cpp 