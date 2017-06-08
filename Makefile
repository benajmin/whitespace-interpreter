WhitespaceInterpreter.out : Command.o Trie.o Main.cpp
	g++ -Wall Trie.o Command.o Main.cpp -o WhitespaceInterpreter.out

Command.o : Command.cpp Command.h
	g++ -Wall -c Command.cpp 

Trie.o : Trie.h Trie.cpp
	g++ -Wall -c Trie.cpp

clear : 
	rm WhitespaceInterpreter.out Trie.o Command.o