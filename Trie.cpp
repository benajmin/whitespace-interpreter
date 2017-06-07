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

	curr->type = type;
}

CommandType Trie::lookup(std::ifstream& input){
	Node* curr = head;

	while (curr->type == nullCmd){
		curr = curr->children[charToInt(input.get())];
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