WhitespaceInterpreter.out : Command.o Trie.o StackWrapper.o Heap.o Main.cpp
	g++ -Wall Trie.o Command.o StackWrapper.o Main.cpp -o WhitespaceInterpreter.out

Command.o : Command.cpp Command.h
	g++ -Wall -c Command.cpp 

Trie.o : Trie.h Trie.cpp
	g++ -Wall -c Trie.cpp

StackWrapper.o : StackWrapper.h StackWrapper.cpp
	g++ -Wall -c StackWrapper.cpp

Heap.o : Heap.h Heap.cpp
	g++ -Wall -c Heap.cpp

clean : 
	rm WhitespaceInterpreter.out Trie.o Command.o StackWrapper.o Heap.o