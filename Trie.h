#ifndef trie
#define trie

#include "Command.h"
#include <iostream>
#include <string>
#include <fstream>

struct Node
{
	CommandType type;
	Node* children[3];
};


class Trie
{
	private:
		Node* head;

		int charToInt(char a);
		Node * newNode();
	public:
		Trie();
		void insert(std::string key, CommandType type);
		CommandType lookup(std::ifstream& input);
};

#endif