#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Command.h"
#include "Trie.h"

std::map<std::string, CommandType> getCommandMap();
void loadSyntax(Trie &trie, bool hasParamater[]);
std::vector<Command> loadProgram(std::string inputFile);

using namespace std;
int main(){
	Trie t;

	ifstream fin ("test");
	t.insert("   ", Pop);
	t.insert("\t\t\t", Push);
	t.insert("\t\n ", Store);

	cout << t.lookup(fin);
	cout << t.lookup(fin);
	return 0;
}

void loadSyntax(Trie &syntaxTrie, bool hasParamater[]){
	ifstream fin ("Syntax.dat");
	std::map<std::string, CommandType> commandMap = Command::getCommandMap();
	std::string syntax;
	std::string commandType;

	while (fin.get()!=EOF){
		std::getline(fin, syntax, '>');
		fin >> commandType;

		//ensure command hasn't been loaded yet
		if (commandMap.find(commandType) != commandMap.end()){
			syntaxTrie.insert(syntax, commandMap[commandType]);
			fin >> hasParamater[commandMap[commandType]];
		}else{
			std::cerr << "Error: Unrecognized command in syntax definitions" << std::endl;
		}
	}
}
