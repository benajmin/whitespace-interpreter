#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Command.h"
#include "Trie.h"
#include "StackWrapper.h"
#include "Heap.h"

void loadSyntax(Trie &trie, bool hasParamater[]);
std::vector<Command> loadProgram(std::string inputFile, Trie syntaxTrie,
	bool hasParamater[], std::map<int, int> labelPositions);
void execute(std::vector<Command> program, StackWrapper stack,
	std::map<int, int> labelPositions, Heap memory);

int main(){
	/*Trie t;

	ifstream fin ("test");
	t.insert("   ", Pop);
	t.insert("\t\t\t", Push);
	t.insert("\t\n ", Store);

	cout << t.lookup(fin);
	cout << t.lookup(fin);*/
	return 0;
}

void loadSyntax(Trie &syntaxTrie, bool hasParamater[]){
	std::ifstream fin ("Syntax.dat");
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

std::vector<Command> loadProgram(std::string inputFile, Trie syntaxTrie,
	bool hasParameter[], std::map<int, int> labelPositions){

	std::ifstream fin (inputFile);
	std::vector<Command> program;
	Command * cmd;
	std::string parameter;

	do{
		cmd = new Command(syntaxTrie.lookup(fin));

		//Set Parameter
		if (cmd->getType() != nullCmd && hasParameter[cmd->getType()]){
			std::getline(fin, parameter);
			cmd->setParameter(parameter);
		}

		//Record label positions
		if (cmd->getType() == Mark){
			if (labelPositions.find(cmd->getParameter()) != labelPositions.end()){
				labelPositions[cmd->getParameter()] = program.size();
			}else{
				std::cerr << "Error: Non-unique labels" << std::endl;
			}
		}

		program.push_back(*cmd);
	}while (cmd->getType() != nullCmd);

	//remove null command
	program.pop_back();

	return program;
}

void execute(std::vector<Command> program, StackWrapper stack,
	std::map<int, int> labelPositions, Heap memory){

	int i = 0;

	while (true){
		switch(program[i].getType()){
			case Push:
				stack.push(program[i].getParameter());
				break;
			case Duplicate:
				stack.duplicate();
				break;
			case Swap:
				stack.swap();
				break;
			case Pop:
				stack.pop();
				break;
			case Add:
				stack.add();
				break;
			case Subtract:
				stack.subtract();
				break;
			case Multiply:
				stack.multiply();
				break;
			case Divide:
				stack.divide();
				break;
			case Mod:
				stack.mod();
				break;
			case Store:
				memory.store(stack.pop(), stack.pop());
				break;
			case Retrieve:
				stack.push(memory.retrieve(stack.pop()));
				break;
			case Mark:
				break;
			case Call:
				break;
			case Jump:
				i = labelPositions[program[i].getParameter()];
				break;
			case JumpZero:
				if (stack.pop() == 0) i = labelPositions[program[i].getParameter()];
				break;
			case JumpNegative:
				if(stack.pop() < 0) i = labelPositions[program[i].getParameter()];
				break;
			case EndSub:
				break;
			case End:
				return;
			case OutChar:
				std::cout << (char) stack.pop();
				break;
			case OutInt:
				std::cout << (int) stack.pop();
				break;
			case InChar:
			case InInt:
				stack.push(std::cin.get());
				break;
			default:
				std::cerr << "Error: Unrecognized command loaded" << std::endl;
				return;
		}
		i++;
	}
}
