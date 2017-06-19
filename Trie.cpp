#include "Trie.h"

Trie::Trie(){
	head =  newNode();
}

void Trie::insert(std::string key, CommandType type){
	Node* curr = head;

	//traverse down tree for each character, creating new nodes as necessary
	for (int i = 0; i < key.length(); i++){
		if (curr->children[charToInt(key[i])] != NULL){
			curr = curr->children[charToInt(key[i])];
		}else{
			curr->children[charToInt(key[i])] = newNode();
			curr = curr->children[charToInt(key[i])];
		}
	}

	//check that we are not overwriting previous commands
	//or creating ambiguous command definitions
	if (curr->type == nullCmd && curr->children[0] == NULL
		&& curr->children[1] == NULL && curr->children[2] == NULL){
		curr->type = type;
	}else{
		std::cerr << "Error: Ambiguous syntax definitions" << std::endl;
		return;
	}
}

CommandType Trie::lookup(std::ifstream& input){
	Node* curr = head;
	char c;

	//traverse down tree untill find defined command
	while (curr->type == nullCmd){
		if (input.eof()){
			return nullCmd;
		}

		c = input.get();

		//skip non whitespace characters
		if (charToInt(c)!=-1){
			//ensure tree is defined for next character
			if (curr->children[charToInt(c)] != NULL){
				curr = curr->children[charToInt(c)];
			}else{
				std::cerr << "Error: Unrecognized command" << std::endl;
				return nullCmd;
			}
		}
	}

	return curr->type;
}

int Trie::charToInt(char a){
	switch(a){
		case ' ': return 0;
		case '\t': return 1;
		case '\n': return 2;
		default: return -1;
	}
}

//Returns new node with members predefined as null
Node * Trie::newNode(){
	Node* node = new Node;
	for (int i = 0; i < 3; i++){
		node->children[i]=NULL;
	}
	node->type = nullCmd;
	return node;
}
