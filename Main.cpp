#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Command.h"
#include "Trie.h"

std::map<std::string, CommandType> getCommandMap();
void loadSyntax(Trie &trie, bool hasParamater[]);

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
	std::map<std::string, CommandType> commandMap = getCommandMap();
	std::string syntax;
	std::string commandType;

	while (fin.get()!=EOF){
		std::getline(fin, syntax, '>');
		fin >> commandType;
		if (commandMap.find(commandType) != commandMap.end()){
			syntaxTrie.insert(syntax, commandMap[commandType]);
			fin >> hasParamater[commandMap[commandType]];
		}else{
			std::cerr << "Error: Unrecognized command in syntax definitions" << std::endl;
		}
	}
}

std::map<std::string, CommandType> getCommandMap(){
	std::map<std::string, CommandType> commandMap;

	commandMap["Push"] = Push;
	commandMap["Duplicate"] = Duplicate;
	commandMap["Swap"] = Swap;
	commandMap["Pop"] = Pop;
	commandMap["Add"] = Add;
	commandMap["Subtract"] = Subtract;
	commandMap["Multiply"] = Multiply;
	commandMap["Divide"] = Divide;
	commandMap["Mod"] = Mod;
	commandMap["Store"] = Store;
	commandMap["Retrieve"] = Retrieve;
	commandMap["Mark"] = Mark;
	commandMap["Call"] = Call;
	commandMap["Jump"] = Jump;
	commandMap["JumpZero"] = JumpZero;
	commandMap["JumpNegative"] = JumpNegative;
	commandMap["EndSub"] = EndSub;
	commandMap["End"] = End;
	commandMap["OutChar"] = OutChar;
	commandMap["OutInt"] = OutInt;
	commandMap["InChar"] = InChar;
	commandMap["InInt"] = InInt;

	return commandMap;
}
