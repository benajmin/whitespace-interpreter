#include "Trie.h"

Trie::Trie(){
	head =  newNode();
}

void Trie::insert(std::string key, CommandType type){
	Node* curr = head;

	for (int i = 0; i < key.length(); i++){
		if (curr->children[charToInt(key[i])] != NULL){
			curr = curr->children[charToInt(key[i])];
		}else{
			curr->children[charToInt(key[i])] = newNode();
			curr = curr->children[charToInt(key[i])];
		}
	}

	if (curr->type == nullCmd && curr->children[0] == NULL 
		&& curr->children[1] == NULL && curr->children[2] == NULL){
		curr->type = type;
	}else{
		std::cerr << "Error: Ambiguous syntax definitions" << std::endl;
	}
}

CommandType Trie::lookup(std::ifstream& input){
	Node* curr = head;
	char c;

	while (curr->type == nullCmd){
		c = input.get();
		if (charToInt(c)!=-1){
			if (curr->children[charToInt(c)] != NULL){
				curr = curr->children[charToInt(c)];
			}else{
				std::cerr << "Error: Unrecognized command" << std::endl;
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

Node * Trie::newNode(){
	Node* node = new Node;
	for (int i = 0; i < 3; i++){
		node->children[i]=NULL;
	}
	node->type = nullCmd;
	return node;
}
